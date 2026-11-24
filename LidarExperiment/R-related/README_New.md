# LiDAR data filtering — LidarExperimentDataCleaned_v2

This tutorial explains how the RPLIDAR A2-M12 raw CSV recordings were converted into the revised dataset for the three experiments. It documents the final processing workflow, excluding exploratory checks, troubleshooting and sensitivity tests.

## 1. Requirements and directory structure

Install R and RStudio Desktop from [CRAN](https://cran.r-project.org/) and [Posit](https://posit.co/download/rstudio-desktop/). On Ubuntu, R can also be installed using `sudo apt update && sudo apt install r-base`.

In RStudio, install the packages once:

```r
install.packages(c("readr", "dplyr", "tidyr"))
```


### 1.1. Required folder structure before filtering

Create a project folder anywhere on your computer. The name `LidarExperiment` is an example.

```text
LidarExperiment/
├── README.md
├── Auto-filtering_final.R
└── LidarExperimentData/
    ├── Experiment01/   # 18 original CSV files
    ├── Experiment02/   # 33 original CSV files
    └── Experiment03/   # 4 original CSV files
```

Save the complete R code in Section 6 as `Auto-filtering_final.R`. Place the original 55 CSV files directly in their corresponding experiment folders. Keep the original filenames and column headings unchanged. The input CSVs must contain the LaserScan metadata and range columns (`ranges`, `ranges_1`, etc.). Distances are in metres and raw angles in radians.

### 1.2. Set the working directory

In RStudio, select **Session → Set Working Directory → Choose Directory** and choose the main project folder (`LidarExperiment` in this example), not `LidarExperimentData` or an experiment subfolder.

Alternatively, run one of the following example commands, replacing the path with your own project location:

```r
# Ubuntu
setwd("/home/student/LidarExperiment")

# macOS
# setwd("/Users/username/Documents/LidarExperiment")

# Windows
# setwd("C:/Users/username/Documents/LidarExperiment")
```

Use only the command appropriate to your computer. The script uses `getwd()` and relative paths, so no other directory paths need to be edited. Open `Auto-filtering_final.R` in RStudio and run it using **Source** after setting the working directory.

### 1.3. Folder structure after filtering

The script automatically creates the output directories and summary files:

```text
LidarExperiment/
├── README.md
├── Auto-filtering_final.R
├── LidarExperimentData/
│   ├── Experiment01/
│   ├── Experiment02/
│   └── Experiment03/
├── LidarExperimentDataCleaned_v2/
│   ├── Experiment01/   # 18 cleaned CSV files
│   ├── Experiment02/   # 33 cleaned CSV files
│   └── Experiment03/   # 4 cleaned CSV files
└── Results/
    └── Tables/
        ├── Experiment01_Scan_Summary.csv
        ├── Experiment02_Final_Filtering_Parameters.csv
        ├── Experiment02_Final_Scan_Summary.csv
        ├── Experiment02_Final_Detection_Summary.csv
        └── Experiment03_Material_Summary.csv
```

## 2. Common preprocessing

Each raw row represents one scan. Convert the range columns into individual ray measurements, preserving the scan number and zero-based ray index. For ray index `k`, calculate `angle_deg = (angle_min + k * angle_increment) * 180 / pi`. A valid return is finite and within the recorded `range_min` and `range_max` (nominally 0.15–16 m). Circular angle differences are wrapped into [-180, 180) degrees.

## 3. Experiment 1 — Distance accuracy

The target is a flat cardboard or whiteboard at nominal distances of 1–5 m in 0.5 m increments.

1. Extract the nominal distance from the filename's metre-valued token.
2. For target discovery only, select valid returns within ±0.10 m of that distance and group them into 1° angular bins. Coverage is the number of distinct scans with a candidate in a bin divided by the total number of scans.
3. Within −175° to −110°, retain bins with at least 90% coverage. Group adjacent bins and choose the widest continuous region (mean coverage breaks ties). Use the midpoint of its outer bin edges as the target centre.
4. Select all rays within ±2° of the centre. Do **not** apply the ±0.10 m distance gate to the final accuracy dataset, because this would truncate measurement errors. Retain validity information.

The selected centres used in the final dataset are:

| Distance (m) | Cardboard (°) | Whiteboard (°) |
|---:|---:|---:|
| 1 | -140 | -133 |
| 1.5 | -139 | -125.5 |
| 2 | -139 | -125.5 |
| 2.5 | -139.5 | -125.5 |
| 3 | -139.5 | -125 |
| 3.5 | -139 | -125 |
| 4 | -139 | -124.5 |
| 4.5 | -139 | -141 |
| 5 | -138 | -140.5 |

## 4. Experiment 2 — Cardboard edge detection

The target is the edge of cardboard with thickness 5.7, 12.5 or 18.1 mm at 1–2 m in 0.1 m increments. Parse thickness and distance separately: `Experiment02_12.5mm_1.1m_10sec.csv` means 12.5 mm thickness and 1.1 m distance, not 12.5 m.

### 4.1 Target direction estimation

The LiDAR orientation changed between groups, while the target was placed in approximately the same direction relative to the room. A single angular window cannot therefore be applied to all recordings.

- Generate candidate angular bins as in Experiment 1. For the 18.1 mm group, select the strongest bin with centre in 168–176° (coverage is the ranking criterion).
- Use the middle scan of `Experiment02_18.1mm_1.2m_10sec.csv` as the reference background. For each recording, extract valid background points between 2.5 and 6 m from its middle scan. Convert polar measurements to Cartesian coordinates: `x = r*cos(theta)`, `y = r*sin(theta)`.
- Rotate the moving cloud through −180° to 179.5° in 0.5° increments. For each rotation, calculate nearest-neighbour distances in both directions using SciPy `cKDTree`. The alignment error is the average of the two median nearest-neighbour distances. Select the rotation with the lowest error.
- For each distance, predict the target direction as the corresponding 18.1 mm reference target angle minus the estimated rotation, wrapped to [-180, 180). This is rotation-only alignment, not full pose estimation.

### 4.2 Final selection

Keep valid returns within ±1° of the predicted target direction and ±0.10 m of the nominal distance. A scan is counted as a candidate detection when at least one ray meets both conditions. Preserve all original scans in a separate summary, including zero-hit scans.

Final centres (degrees), in ascending distance order:

| Distance (m) | 5.7 mm | 12.5 mm | 18.1 mm |
|---:|---:|---:|---:|
| 1 | -103 | -103.5 | 169.5 |
| 1.1 | -101.5 | -101.5 | 171.5 |
| 1.2 | -101 | -101.5 | 171.5 |
| 1.3 | -100 | -100.5 | 172.5 |
| 1.4 | -101.5 | -101 | 171.5 |
| 1.5 | -100.5 | -100.5 | 172.5 |
| 1.6 | -100.5 | -100.5 | 172.5 |
| 1.7 | -100.5 | -100.5 | 172.5 |
| 1.8 | -100 | -100.5 | 172.5 |
| 1.9 | -100.5 | -100.5 | 172.5 |
| 2 | -101.5 | -120 | 171.5 |

The 18.1 mm centres are provisional; the thinner groups are conditional on the predicted location. The 12.5 mm recording at 2 m is uncertain because of its exceptional rotation estimate. Retain it in the exported data but exclude it from primary detection-rate conclusions.

## 5. Experiment 3 — Material interference

The target was nominally 30 cm away, with Organza, Polyester or Satin placed 5 cm in front of the sensor. The no-material recording provides the reference.

1. Select rays between −175° and −125° in the no-material recording.
2. For each ray index, calculate the median valid distance and median angle as the baseline.
3. Select the same angular region for every material recording and join the baseline by ray index.
4. Classify each ray as `unmatched_baseline` (missing reference or angular difference greater than 0.05°), `invalid` (invalid sensor return), `consistent` (valid return within ±0.02 m of baseline), or `inconsistent` (other valid return).
5. Preserve all selected rays, including invalid and inconsistent returns. Calculate signed distance error relative to the baseline for valid rays.

## 6. Reproduce the final exports in RStudio

The following consolidated script uses the final centres above instead of repeating target discovery. It reconstructs the filtering workflow; it is not a verbatim copy of the original multi-stage scripts. Save it as `Auto-filtering_final.R` in the project root and set the RStudio working directory to that root before running it. It overwrites same-named outputs in `LidarExperimentDataCleaned_v2` and the listed summary files; keep a backup if needed.

```r
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
```

## 7. Output and interpretation

The workflow produces 55 cleaned CSVs (18, 33 and 4 respectively), with `_cleaned` appended to the original filename. Experiment 1 uses 126,800 selected rays across 6,340 scans in the original run. Experiment 2 preserves 3,741 scans in its summary, including 1,242 with matching returns and 2,499 without. Some Experiment 2 cleaned files contain only headers; keep them and use the scan summary for detection-rate denominators. Experiment 3 uses the outcome labels to calculate material consistency and invalid-return rates.

The final parameter tables are specific to this recording setup. For new recordings, repeat target identification rather than reuse the angles blindly. Candidate discovery uses a nominal-distance gate and may favour returns near that distance. Experiment 1 reference distances are approximate manual measurements. Experiment 2 rotation correction assumes approximately unchanged target direction and does not correct translation; a missing candidate is not proof of physical non-detection. Experiment 3 measures agreement with the no-material baseline, not absolute accuracy against the nominal 30 cm distance.
