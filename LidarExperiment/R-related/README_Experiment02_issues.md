# Experiment 2 --- LiDAR filtering issues and Auto-filtering v3

## 1. Experiment overview

Experiment 2 investigates the ability of the RPLIDAR A2-M12 to detect cardboard edges of different thicknesses.

-   Thicknesses: 5.7 mm, 12.5 mm and 18.1 mm.
-   Nominal distances: 1.0--2.0 m in 0.1 m increments.
-   33 recordings (11 per thickness), approximately 10 seconds each.
-   3,741 scans in total.

Each raw CSV row represents a scan. The `ranges` and `ranges_N` columns contain individual distance measurements in metres.

## 2. Why the filtering method was revised

The original filtering workflow could confuse the thickness token in a filename with the nominal distance. For example, `Experiment02_12.5mm_1.9m_10sec.csv` represents a 12.5 mm cardboard edge at 1.9 m, not a target at 12.5 m.

The v2 workflow corrected the filename parsing and attempted to isolate the target using a predicted angular centre, a ±1° angular window and a ±0.10 m distance window. However, the LiDAR orientation changed during the experiment. Background point-cloud alignment was used to estimate rotation, but the actual target directions for the thinner cardboard could not be established reliably. Rotation-only alignment also cannot correct translation or changes in target placement.

The experimenter observed cardboard returns during data collection, yet v2 produced 20 header-only CSV files. A missing return after filtering is therefore not necessarily a physical non-detection.

## 3. Angular sensitivity investigation

To test the effect of angular restriction, the v2 predicted centres were retained while the angular half-width was increased. The distance tolerance remained ±0.10 m throughout.

### Percentage of scans with at least one matching return

  Thickness       ±1°    ±10°    ±30°    ±60°    ±90°   Full circle
  ----------- ------- ------- ------- ------- ------- -------------
  5.7 mm        1.85%   7.55%   7.55%   7.55%   50.2%         70.5%
  12.5 mm          0%      0%      0%      0%   42.4%         70.1%
  18.1 mm       93.1%   93.1%   93.1%   93.2%   94.5%         96.5%

### Overall retention

  Angular half-width           Retained measurements   Empty recordings
  -------------------------- ----------------------- ------------------
  ±1° (v2)                                     5,802                 20
  ±10°                                         6,415                 14
  ±30°                                         6,415                 14
  ±60°                                         6,537                 14
  ±90°                                        22,572                  7
  ±180° (equivalent to v3)                    87,730                  1

The 18.1 mm results are comparatively insensitive to angular width, whereas the thinner groups are strongly affected. This may reflect incorrect predicted target directions, background interference, or both. These comparisons are from the angular sensitivity workflow; a larger retained count does not demonstrate better target identification.

## 4. Auto-filtering_v3.R --- distance-only method

V3 removes the angular restriction and retains every finite return within the sensor's recorded range limits and ±0.10 m of the nominal target distance. For a nominal distance of 1.9 m, the accepted interval is 1.8--2.0 m.

The selection rule is:

``` text
finite(distance)
AND range_min <= distance <= range_max
AND abs(distance - nominal_distance) <= 0.10
```

Angles are calculated and retained for subsequent spatial analysis, but are not used to select returns. All original scans, including scans with zero matches, are represented in the separate scan summary. Raw data and earlier cleaned versions are not modified.

### Verified v3 results

The following totals were independently recalculated from all 33 original Experiment 2 CSV files.

  -----------------------------------------------------------------------------------------------------------------
  Thickness     Total scans   Matched scans   Unmatched scans   Matching rate   Retained measurements   Empty files
  ----------- ------------- --------------- ----------------- --------------- ----------------------- -------------
  5.7 mm              1,192             840               352          70.47%                  26,614             0

  12.5 mm             1,239             868               371          70.06%                  35,057             1

  18.1 mm             1,310           1,264                46          96.49%                  26,059             0

  Total               3,741           2,972               769          79.44%                  87,730             1
  -----------------------------------------------------------------------------------------------------------------

Matching rate = 100 × number of scans with at least one retained return / total original scans. It is not a verified cardboard detection probability.

## 5. Investigation of the empty 1.9 m recording

The remaining empty file is `Experiment02_12.5mm_1.9m_10sec_cleaned.csv`.

Direct inspection of the three uploaded raw recordings gave the following results:

  ---------------------------------------------------------------------------------------------------------
  Nominal distance      Total scans   Valid returns (all distances)   Returns within ±10 cm   Matched scans
  ------------------ -------------- ------------------------------- ----------------------- ---------------
  1.8 m                         116                         122,089                     583              80

  1.9 m                         117                         113,431                       0               0

  2.0 m                         118                         121,402                      68              14
  ---------------------------------------------------------------------------------------------------------

The 1.9 m file contains 210,600 raw rays, including 113,431 valid returns. It contains no valid returns in the interval 1.8--2.0 m. Thus the empty output is consistent with the recorded values, not a failure of the v3 distance filter.

### Distance sensitivity for the 1.9 m recording

  Tolerance     Retained returns   Matched scans (out of 117)
  ----------- ------------------ ----------------------------
  ±10 cm                       0                            0
  ±15 cm                       0                            0
  ±20 cm                     157                           30
  ±25 cm                     894                          106
  ±30 cm                   2,917                          117

The closest valid return to 1.9 m is approximately 1.712 m, a difference of 18.8 cm. The nearby returns could represent a displaced target or a background object. The raw data alone does not establish their identity. Returns in the adjacent recordings do not prove that the cardboard was detected there either.

Keep the empty CSV and its original scan denominator. Do not selectively increase the tolerance for this recording simply to obtain data. Any wider tolerance should be investigated consistently across all recordings.

## 6. Reproduce the v3 filtering in RStudio

Install R and RStudio if required. In the R console, install the packages once:

``` r
install.packages(c("readr", "dplyr", "tidyr"))
```

Set the working directory to the project root using **Session → Set Working Directory → Choose Directory**. The example uses the current project folder names. If your raw folder is named `RawData` instead, change the `raw_folder` line accordingly.

Save the following reconstructed, portable version as `Auto-filtering_v3.R` and run it using **Source**. It implements the same distance-only selection as the v3 workflow.

``` r
library(readr)
library(dplyr)
library(tidyr)

project_folder <- getwd()
raw_folder <- file.path(project_folder, "LidarExperimentData", "Experiment02")
output_folder <- file.path(project_folder, "LidarExperimentDataCleaned_v3", "Experiment02")
tables_folder <- file.path(project_folder, "Results", "Tables")
dir.create(output_folder, recursive = TRUE, showWarnings = FALSE)
dir.create(tables_folder, recursive = TRUE, showWarnings = FALSE)

pattern <- "^Experiment02_([0-9.]+)mm_([0-9.]+)m_10sec\\.csv$"
files <- list.files(raw_folder, pattern = pattern, full.names = TRUE)
stopifnot(length(files) == 33)
tolerance <- 0.10
results <- list()
scans <- list()

for (i in seq_along(files)) {
  filename <- basename(files[i])
  thickness <- as.numeric(sub(pattern, "\\1", filename))
  expected_distance <- as.numeric(sub(pattern, "\\2", filename))
  raw <- read_csv(files[i], show_col_types = FALSE)
  total_scans <- nrow(raw)
  stopifnot(total_scans > 0)

  data <- raw %>%
    mutate(scan_number = row_number()) %>%
    pivot_longer(cols = matches("^ranges(_[0-9]+)?$"),
                 names_to = "range_column", values_to = "distance") %>%
    mutate(measurement = as.integer(sub("^ranges_?", "",
                         sub("^ranges$", "ranges_0", range_column))),
           angle_deg = (angle_min + measurement * angle_increment) * 180 / pi) %>%
    select(scan_number, measurement, angle_deg, distance, range_min, range_max)

  filtered <- data %>%
    filter(is.finite(distance), distance >= range_min,
           distance <= range_max, abs(distance - expected_distance) <= tolerance)

  write_csv(filtered, file.path(output_folder,
                               sub("\\.csv$", "_cleaned.csv", filename)))

  scan_summary <- tibble(scan_number = seq_len(total_scans)) %>%
    left_join(count(filtered, scan_number, name = "matching_points"),
              by = "scan_number") %>%
    mutate(matching_points = coalesce(matching_points, 0L),
           distance_matched = matching_points > 0,
           Filename = filename, Thickness_mm = thickness,
           Expected_Distance = expected_distance)

  matched <- sum(scan_summary$distance_matched)
  scans[[i]] <- scan_summary
  results[[i]] <- tibble(
    Filename = filename, Thickness_mm = thickness,
    Expected_Distance = expected_distance, Tolerance_m = tolerance,
    Total_Scans = total_scans, Matched_Scans = matched,
    Unmatched_Scans = total_scans - matched,
    Matching_Rate_Percent = 100 * matched / total_scans,
    Retained_Measurements = nrow(filtered),
    Mean_Points_Per_Scan = nrow(filtered) / total_scans)
}

exp2_summary_v3 <- bind_rows(results)
exp2_scan_summary_v3 <- bind_rows(scans)
write_csv(exp2_summary_v3, file.path(tables_folder,
          "Experiment02_Distance_Matching_Summary_v3.csv"))
write_csv(exp2_scan_summary_v3, file.path(tables_folder,
          "Experiment02_Scan_Summary_v3.csv"))
```

The script overwrites same-named v3 outputs if rerun. It does not process Experiments 1 or 3. The 33-file check is specific to this experiment; adjust it only if intentionally processing a different dataset.

## 7. Output structure

``` text
LidarWorkings/
├── Auto-filtering_v3.R
├── LidarExperimentData/
│   └── Experiment02/                 # 33 raw CSVs
├── LidarExperimentDataCleaned_v3/
│   └── Experiment02/                 # 33 cleaned CSVs (1 header-only)
└── Results/
    └── Tables/
        ├── Experiment02_Distance_Matching_Summary_v3.csv
        └── Experiment02_Scan_Summary_v3.csv
```

## 8. Limitations and final dataset choice

V3 is recommended for exploratory Experiment 2 analysis because the target angles are uncertain. It is not proven to isolate the cardboard more accurately than v2. Background objects at similar distances can be retained, while genuine returns outside the tolerance can be removed. Distance-gated returns should not be used to claim unbiased absolute range accuracy. Repeated rays and scans are also not necessarily independent observations.

Use the terms **distance-matching rate** and **potential target returns**, rather than confirmed detection rate. The recommended datasets for Experiments 1 and 3 remain their v2 outputs; v3 only replaces the primary exploratory dataset for Experiment 2.

