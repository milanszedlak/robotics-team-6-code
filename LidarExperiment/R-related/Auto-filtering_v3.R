library(readr)
library(dplyr)
library(tidyr)

project_folder <- paste0(
  "/Users/hanzhang/Library/CloudStorage/",
  "OneDrive-TheUniversityofManchester/",
  "Courses/Robotic System/Courseworks/",
  "CWK2/LidarWorkings"
)

raw_folder <- file.path(
  project_folder,
  "LidarExperimentData",
  "Experiment02"
)

output_folder <- file.path(
  project_folder,
  "LidarExperimentDataCleaned_v3",
  "Experiment02"
)

tables_folder <- file.path(
  project_folder,
  "Results",
  "Tables"
)

dir.create(
  output_folder,
  recursive = TRUE,
  showWarnings = FALSE
)

exp2_files <- list.files(
  raw_folder,
  pattern = "\\.csv$",
  full.names = TRUE
)

cat("Raw CSV files found:", length(exp2_files))



exp2_parameters <- tibble(
  Filename = basename(exp2_files)
) %>%
  mutate(
    Thickness_mm = as.numeric(
      sub(
        "^Experiment02_([0-9.]+)mm_.*$",
        "\\1",
        Filename
      )
    ),
    
    Expected_Distance = as.numeric(
      sub(
        "^Experiment02_[0-9.]+mm_([0-9.]+)m_.*$",
        "\\1",
        Filename
      )
    ),
    
    Tolerance_m = 0.10,
    
    Lower_Limit = Expected_Distance - Tolerance_m,
    
    Upper_Limit = Expected_Distance + Tolerance_m
  )

print(exp2_parameters, n = 33, width = Inf)


dir.create(
  tables_folder,
  recursive = TRUE,
  showWarnings = FALSE
)



# ============================================================
# EXPERIMENT 2 - DISTANCE-ONLY FILTERING
# ============================================================

dir.create(
  tables_folder,
  recursive = TRUE,
  showWarnings = FALSE
)

detection_results_v3 <- list()
scan_results_v3 <- list()

for (i in seq_len(nrow(exp2_parameters))) {
  
  parameters <- exp2_parameters[i, ]
  
  filename <- parameters$Filename
  expected_distance <- parameters$Expected_Distance
  tolerance <- parameters$Tolerance_m
  
  # Load original CSV
  raw_data <- read_csv(
    file.path(raw_folder, filename),
    show_col_types = FALSE
  )
  
  total_scans <- nrow(raw_data)
  
  # Convert from wide format to long format
  data <- raw_data %>%
    mutate(scan_number = row_number()) %>%
    pivot_longer(
      cols = matches("^ranges(_[0-9]+)?$"),
      names_to = "range_column",
      values_to = "distance"
    ) %>%
    mutate(
      measurement = as.integer(
        sub("^ranges_?", "", range_column) %>%
          replace(range_column == "ranges", "0")
      ),
      
      angle_deg = (
        angle_min +
          measurement * angle_increment
      ) * 180 / pi
    ) %>%
    select(
      scan_number,
      measurement,
      angle_deg,
      distance,
      range_min,
      range_max
    )
  
  # Apply distance-only filtering
  filtered <- data %>%
    filter(
      is.finite(distance),
      distance >= range_min,
      distance <= range_max,
      abs(distance - expected_distance) <= tolerance
    )
  
  # Generate cleaned filename
  cleaned_name <- sub(
    "\\.csv$",
    "_cleaned.csv",
    filename
  )
  
  # Export cleaned CSV
  write_csv(
    filtered,
    file.path(output_folder, cleaned_name)
  )
  
  # Preserve all original scans
  scan_summary <- tibble(
    scan_number = seq_len(total_scans)
  ) %>%
    left_join(
      filtered %>%
        count(
          scan_number,
          name = "matching_points"
        ),
      by = "scan_number"
    ) %>%
    mutate(
      matching_points = replace_na(
        matching_points, 0L
      ),
      distance_matched = matching_points > 0,
      Filename = filename,
      Thickness_mm = parameters$Thickness_mm,
      Expected_Distance = expected_distance
    )
  
  matched_scans <- sum(
    scan_summary$distance_matched
  )
  
  # Recording-level summary
  detection_results_v3[[i]] <- tibble(
    Filename = filename,
    Thickness_mm = parameters$Thickness_mm,
    Expected_Distance = expected_distance,
    Tolerance_m = tolerance,
    Total_Scans = total_scans,
    Matched_Scans = matched_scans,
    Unmatched_Scans = total_scans - matched_scans,
    Matching_Rate_Percent =
      matched_scans / total_scans * 100,
    Retained_Measurements = nrow(filtered),
    Mean_Points_Per_Scan =
      nrow(filtered) / total_scans
  )
  
  scan_results_v3[[i]] <- scan_summary
  
  cat(
    "Completed:", filename,
    "| Retained:", nrow(filtered),
    "| Matched scans:", matched_scans,
    "/", total_scans,
    "\n"
  )
}

# Combine all recording summaries
exp2_summary_v3 <- bind_rows(
  detection_results_v3
)

# Combine all scan summaries
exp2_scan_summary_v3 <- bind_rows(
  scan_results_v3
)

# Export recording-level summary
write_csv(
  exp2_summary_v3,
  file.path(
    tables_folder,
    "Experiment02_Distance_Matching_Summary_v3.csv"
  )
)

# Export scan-level summary
write_csv(
  exp2_scan_summary_v3,
  file.path(
    tables_folder,
    "Experiment02_Scan_Summary_v3.csv"
  )
)

cat("\nExperiment 2 distance-only filtering completed.\n")

exp2_summary_v3 %>%
  group_by(Thickness_mm) %>%
  summarise(
    Recordings = n(),
    Total_Scans = sum(Total_Scans),
    Matched_Scans = sum(Matched_Scans),
    Unmatched_Scans = sum(Unmatched_Scans),
    Retained_Measurements = sum(Retained_Measurements),
    Empty_Files = sum(Retained_Measurements == 0),
    Matching_Rate_Percent = round(
      Matched_Scans / Total_Scans * 100,
      2
    ),
    .groups = "drop"
  ) %>%
  print(width = Inf)
