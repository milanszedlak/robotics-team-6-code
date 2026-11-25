library(readr)
library(dplyr)
library(tidyr)
root <- getwd()
input <- file.path(root, "LidarExperimentData")
output <- file.path(root, "LidarExperimentDataCleaned_v2")
tables <- file.path(root, "Results", "Tables")
dir.create(tables, recursive = TRUE, showWarnings = FALSE)
wrap <- function(x) (x + 180) %% 360 - 180
convert <- function(file) {
  read_csv(file, show_col_types = FALSE) %>%
    mutate(scan_number = row_number()) %>%
    pivot_longer(matches("^ranges(_[0-9]+)?$"),
                 names_to = "range_column", values_to = "distance") %>%
    mutate(measurement = as.integer(sub("^ranges_?", "",
                                        sub("^ranges$", "ranges_0", range_column))),
           angle_deg = (angle_min + measurement * angle_increment) * 180 / pi,
           valid = is.finite(distance) & distance >= range_min & distance <= range_max) %>%
    select(scan_number, measurement, angle_deg, distance, range_min, range_max, valid)
}
files <- function(exp) list.files(file.path(input, exp),
                                  pattern = "[.]csv$", full.names = TRUE)
export <- function(d, f, exp) {
  dir.create(file.path(output, exp), recursive = TRUE, showWarnings = FALSE)
  write_csv(d, file.path(output, exp, sub("[.]csv$", "_cleaned.csv", basename(f))))
}

# Experiment 1: fixed final target centres
p1 <- tibble(Distance = seq(1, 5, 0.5),
             cardboard = c(-140,-139,-139,-139.5,-139.5,-139,-139,-139,-138),
             whiteboard = c(-133,-125.5,-125.5,-125.5,-125,-125,-124.5,-141,-140.5)) %>%
  pivot_longer(-Distance, names_to = "Material", values_to = "Centre")
s1 <- list()
for (f in files("Experiment01")) {
  tokens <- strsplit(sub("[.]csv$", "", basename(f)), "_")[[1]]
  ref <- as.numeric(sub("m$", "", tokens[2]))
  p <- filter(p1, Distance == ref, Material == tokens[3])
  d <- convert(f)
  selected <- d %>% filter(abs(wrap(angle_deg - p$Centre)) <= 2) %>%
    mutate(outcome = if_else(valid, "valid", "invalid"))
  export(selected, f, "Experiment01")
  s1[[basename(f)]] <- tibble(scan_number = unique(d$scan_number)) %>%
    left_join(selected %>% group_by(scan_number) %>%
                summarise(valid_points = sum(valid),
                          median_distance = if (any(valid)) median(distance[valid]) else NA_real_,
                          .groups = "drop"), by = "scan_number") %>%
    mutate(Filename = basename(f), reference_m = ref, approved = TRUE,
           valid_points = coalesce(valid_points, 0L))
}
write_csv(bind_rows(s1), file.path(tables, "Experiment01_Scan_Summary.csv"))

# Experiment 2: rotation-corrected final parameters
p2 <- tibble(Distance_m = round(seq(1, 2, 0.1), 1),
             `5.7` = c(-103,-101.5,-101,-100,-101.5,-100.5,-100.5,-100.5,-100,-100.5,-101.5),
             `12.5` = c(-103.5,-101.5,-101.5,-100.5,-101,-100.5,-100.5,-100.5,-100.5,-100.5,-120),
             `18.1` = c(169.5,171.5,171.5,172.5,171.5,172.5,172.5,172.5,172.5,172.5,171.5)) %>%
  pivot_longer(-Distance_m, names_to = "Thickness_mm", values_to = "Centre_Angle") %>%
  mutate(Thickness_mm = as.numeric(Thickness_mm), Half_Width = 1, Tolerance_m = 0.10,
         Filename = paste0("Experiment02_", Thickness_mm, "mm_", Distance_m, "m_10sec.csv"),
         Validation_Status = case_when(Thickness_mm == 18.1 ~ "Provisional",
                                       Thickness_mm == 12.5 & Distance_m == 2 ~ "Uncertain", TRUE ~ "Conditional")) %>%
  select(Filename, Thickness_mm, Distance_m, Centre_Angle, Half_Width, Tolerance_m, Validation_Status)
write_csv(p2, file.path(tables, "Experiment02_Final_Filtering_Parameters.csv"))
s2 <- list(); results2 <- list()
for (i in seq_len(nrow(p2))) {
  p <- p2[i, ]; f <- file.path(input, "Experiment02", p$Filename)
  d <- convert(f)
  selected <- d %>% mutate(angle_difference = wrap(angle_deg - p$Centre_Angle)) %>%
    filter(valid, abs(angle_difference) <= p$Half_Width,
           abs(distance - p$Distance_m) <= p$Tolerance_m) %>%
    select(-valid) %>% mutate(validation_status = p$Validation_Status)
  export(selected, f, "Experiment02")
  s <- tibble(scan_number = unique(d$scan_number)) %>%
    left_join(count(selected, scan_number, name = "matching_points"), by = "scan_number") %>%
    mutate(matching_points = coalesce(matching_points, 0L),
           candidate_detected = matching_points > 0,
           Filename = p$Filename, Validation_Status = p$Validation_Status)
  s2[[i]] <- s
  results2[[i]] <- p %>% rename(Expected_Distance = Distance_m) %>%
    mutate(Total_Scans = nrow(s), Detected_Scans = sum(s$candidate_detected),
           Undetected_Scans = Total_Scans - Detected_Scans,
           Detection_Rate_Percent = 100 * Detected_Scans / Total_Scans,
           Retained_Measurements = nrow(selected))
}
write_csv(bind_rows(s2), file.path(tables, "Experiment02_Final_Scan_Summary.csv"))
write_csv(bind_rows(results2), file.path(tables, "Experiment02_Final_Detection_Summary.csv"))

# Experiment 3: per-ray baseline comparison
f3 <- files("Experiment03")
baseline <- convert(f3[grepl("Experiment03_Nomaterial_", basename(f3))]) %>%
  filter(angle_deg >= -175, angle_deg <= -125, valid) %>%
  group_by(measurement) %>% summarise(baseline_distance = median(distance),
                                      baseline_angle = median(angle_deg), .groups = "drop")
s3 <- list()
for (f in f3) {
  selected <- convert(f) %>% filter(angle_deg >= -175, angle_deg <= -125) %>%
    left_join(baseline, by = "measurement") %>%
    mutate(distance_error = if_else(valid, distance - baseline_distance, NA_real_),
           outcome = case_when(is.na(baseline_distance) | abs(angle_deg - baseline_angle) > 0.05 ~ "unmatched_baseline",
                               !valid ~ "invalid", abs(distance_error) <= 0.02 ~ "consistent", TRUE ~ "inconsistent"))
  export(selected, f, "Experiment03")
  s3[[basename(f)]] <- selected %>% count(scan_number, outcome, name = "points") %>%
    mutate(Filename = basename(f))
}
write_csv(bind_rows(s3), file.path(tables, "Experiment03_Material_Summary.csv"))

