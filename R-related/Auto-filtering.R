# ============================================================
# AUTOMATIC LiDAR DATA FILTERING
# Experiments 1, 2 and 3
# ============================================================

install.packages(c("readr", "dplyr", "tidyr", "purrr")) # run once on the machine is enough (it's ok if you run it multiple times)

library(readr)
library(dplyr)
library(tidyr)
library(purrr)


# ============================================================
# 1. FOLDER SETTINGS
# ============================================================

input_folder <- "~/LidarExperimentData"

output_folder <- file.path(
  input_folder,
  "AutoFiltered"
)

dir.create(
  output_folder,
  recursive = TRUE,
  showWarnings = FALSE
)


# ============================================================
# 2. CONVERT RAW LiDAR CSV TO LONG FORMAT
# ============================================================

convert_lidar <- function(file) {
  
  data <- read_csv(
    file,
    show_col_types = FALSE
  )
  
  data %>%
    mutate(
      scan_number = row_number()
    ) %>%
    pivot_longer(
      cols = matches("^ranges(_[0-9]+)?$"),
      names_to = "range_column",
      values_to = "distance"
    ) %>%
    mutate(
      measurement = if_else(
        range_column == "ranges",
        0L,
        as.integer(sub("ranges_", "", range_column))
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
}


# ============================================================
# 3. ADD "_cleaned" TO EXPORTED CSV FILENAMES
# ============================================================

cleaned_filename <- function(filename) {
  
  sub(
    "\\.csv$",
    "_cleaned.csv",
    filename,
    ignore.case = TRUE
  )
}


# ============================================================
# 4. FIND EXPERIMENT FILES
# ============================================================

all_files <- list.files(
  input_folder,
  pattern = "^Experiment0[123]_.*\\.csv$",
  recursive = TRUE,
  full.names = TRUE
)

# Exclude previously generated output folders
all_files <- all_files[
  !grepl(
    "/(AutoFiltered|Experiment0[123]_AutoFiltered|Experiment03_Cleaned|Experiment03_BaselineComparison)/",
    all_files
  )
]

# Exclude previously cleaned files
all_files <- all_files[
  !grepl(
    "_cleaned\\.csv$",
    all_files,
    ignore.case = TRUE
  )
]

exp1_files <- all_files[
  grepl("^Experiment01_", basename(all_files))
]

exp2_files <- all_files[
  grepl("^Experiment02_", basename(all_files))
]

exp3_files <- all_files[
  grepl("^Experiment03_", basename(all_files))
]


# ============================================================
# 5. EXTRACT EXPECTED DISTANCE FROM FILENAME
# ============================================================

extract_distance <- function(filename) {
  
  match <- regmatches(
    filename,
    regexpr(
      "[0-9]+(\\.[0-9]+)?(cm|m)",
      filename
    )
  )
  
  if (length(match) == 0 || match == "") {
    return(NA_real_)
  }
  
  if (grepl("cm$", match)) {
    return(
      as.numeric(sub("cm$", "", match)) / 100
    )
  }
  
  as.numeric(sub("m$", "", match))
}


# ============================================================
# 6. EXPERIMENT 1: DISTANCE-BASED AUTO-FILTER
# ============================================================

exp1_tolerance <- 0.10

exp1_output <- file.path(
  output_folder,
  "Experiment01"
)

dir.create(
  exp1_output,
  showWarnings = FALSE
)

for (file in exp1_files) {
  
  filename <- basename(file)
  
  expected_distance <- extract_distance(filename)
  
  if (is.na(expected_distance)) {
    warning("Cannot determine distance: ", filename)
    next
  }
  
  data <- convert_lidar(file)
  
  filtered <- data %>%
    filter(
      is.finite(distance),
      distance >= range_min,
      distance <= range_max,
      abs(distance - expected_distance) <= exp1_tolerance
    )
  
  write_csv(
    filtered,
    file.path(
      exp1_output,
      cleaned_filename(filename)
    )
  )
  
  cat(
    "Experiment 1:",
    filename,
    "-",
    nrow(filtered),
    "measurements retained\n"
  )
}


# ============================================================
# 7. EXPERIMENT 2: DISTANCE-BASED AUTO-FILTER
# ============================================================

exp2_tolerance <- 0.10

exp2_output <- file.path(
  output_folder,
  "Experiment02"
)

dir.create(
  exp2_output,
  showWarnings = FALSE
)

for (file in exp2_files) {
  
  filename <- basename(file)
  
  expected_distance <- extract_distance(filename)
  
  if (is.na(expected_distance)) {
    warning("Cannot determine distance: ", filename)
    next
  }
  
  data <- convert_lidar(file)
  
  filtered <- data %>%
    filter(
      is.finite(distance),
      distance >= range_min,
      distance <= range_max,
      abs(distance - expected_distance) <= exp2_tolerance
    )
  
  write_csv(
    filtered,
    file.path(
      exp2_output,
      cleaned_filename(filename)
    )
  )
  
  cat(
    "Experiment 2:",
    filename,
    "-",
    nrow(filtered),
    "measurements retained\n"
  )
}


# ============================================================
# 8. EXPERIMENT 3: BASELINE-BASED AUTO-FILTER
# ============================================================

exp3_output <- file.path(
  output_folder,
  "Experiment03"
)

dir.create(
  exp3_output,
  showWarnings = FALSE
)

baseline_file <- exp3_files[
  grepl(
    "Nomaterial",
    basename(exp3_files),
    ignore.case = TRUE
  )
]

if (length(baseline_file) != 1) {
  stop("Expected exactly one Experiment 3 baseline file.")
}

baseline_data <- convert_lidar(baseline_file)

baseline_reference <- baseline_data %>%
  filter(
    angle_deg >= -175,
    angle_deg <= -125,
    is.finite(distance),
    distance >= range_min,
    distance <= range_max
  ) %>%
  group_by(measurement) %>%
  summarise(
    baseline_distance = median(distance),
    .groups = "drop"
  )

exp3_tolerance <- 0.02

for (file in exp3_files) {
  
  filename <- basename(file)
  
  data <- convert_lidar(file)
  
  filtered <- data %>%
    filter(
      angle_deg >= -175,
      angle_deg <= -125
    ) %>%
    left_join(
      baseline_reference,
      by = "measurement"
    ) %>%
    filter(
      is.finite(distance),
      distance >= range_min,
      distance <= range_max,
      !is.na(baseline_distance),
      abs(distance - baseline_distance) <= exp3_tolerance
    ) %>%
    mutate(
      distance_error = distance - baseline_distance
    )
  
  write_csv(
    filtered,
    file.path(
      exp3_output,
      cleaned_filename(filename)
    )
  )
  
  cat(
    "Experiment 3:",
    filename,
    "-",
    nrow(filtered),
    "measurements retained\n"
  )
}


# ============================================================
# 9. FINISHED
# ============================================================

cat("\nAutomatic filtering completed.\n")
cat("Output folder:", output_folder, "\n")

