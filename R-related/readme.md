## Installing R and RStudio on Ubuntu

This tutorial explains how to install **R** and **RStudio Desktop** on Ubuntu before running the automatic LiDAR data-filtering script.

The instructions are intended for beginners using Ubuntu 22.04, 24.04 or 26.04 LTS on a 64-bit Intel/AMD computer.

### 1. Install R

R is the programming language used to process and analyse the LiDAR CSV files.

#### Step 1.1: Open Terminal

Press `Ctrl + Alt + T` to open a terminal.

#### Step 1.2: Update Ubuntu

```bash
sudo apt update
sudo apt upgrade -y
```

#### Step 1.3: Install R

Run:

```bash
sudo apt install r-base r-base-dev -y
```

This installs R from Ubuntu's package repositories.

For instructions on installing the latest R release, see the official CRAN Ubuntu installation guide.

#### Step 1.4: Verify the installation

```bash
R --version
```

If R is installed successfully, the terminal will display its version information.

You can also start R by typing:

```bash
R
```

To exit R:

```r
q()
```

When prompted to save the workspace, select `n` if you do not need to save it.

---

### 2. Install RStudio Desktop

RStudio is an integrated development environment (IDE) that makes it easier to write, run and debug R code.

#### Step 2.1: Download RStudio

Visit the official RStudio download page:

**RStudio Desktop:** https://posit.co/download/rstudio-desktop/

Select:

1. **RStudio Desktop — Open Source Edition**
2. **Ubuntu / Debian**
3. Download the `.deb` installer.

Make sure you download the installer compatible with your Ubuntu version and computer architecture.

#### Step 2.2: Install RStudio

Open Terminal and navigate to your Downloads folder:

```bash
cd ~/Downloads
```

Install the downloaded package:

```bash
sudo apt install ./rstudio-*.deb
```

If multiple RStudio installers are present, specify the exact downloaded filename instead.

#### Step 2.3: Launch RStudio

After installation, open RStudio from the Ubuntu applications menu.

Alternatively, run:

```bash
rstudio
```

RStudio should open and automatically detect your R installation.

---

### 3. Install Required R Packages

The automatic LiDAR filtering script requires four R packages:

- `readr` — Reading and writing CSV files.
- `dplyr` — Filtering and manipulating data.
- `tidyr` — Reshaping LiDAR measurements.
- `purrr` — Supporting data-processing operations.

Open RStudio and enter the following command in the **Console**:

```r
install.packages(c(
  "readr",
  "dplyr",
  "tidyr",
  "purrr"
))
```

Wait until the installation finishes.

Then load the packages:

```r
library(readr)
library(dplyr)
library(tidyr)
library(purrr)
```

If no errors appear, the packages have loaded successfully.

---

### 4. Prepare the LiDAR Data Folder

Create a folder called `LidarExperimentData` inside your Ubuntu Home directory.

You can do this using Terminal:

```bash
mkdir -p ~/LidarExperimentData
```

Organise your original CSV files into the following structure:

```text
Home/
└── LidarExperimentData/
    ├── Experiment01/
    │   └── Experiment 1 CSV files
    │
    ├── Experiment02/
    │   └── Experiment 2 CSV files
    │
    └── Experiment03/
        └── Experiment 3 CSV files
```

The filtering script automatically searches these folders for CSV files beginning with `Experiment01_`, `Experiment02_` or `Experiment03_`.

---

### 5. Run the Automatic LiDAR Filtering Script

#### Step 5.1: Open RStudio

Launch RStudio.

#### Step 5.2: Create an R script

In RStudio:

1. Select **File → New File → R Script**.
2. Copy the automatic LiDAR filtering code from the next section of this README.
3. Paste the code into the script editor.
4. Save the file as `AutoFilter_LiDAR.R`.

#### Step 5.3: Run the script

Click **Source** in the top-right corner of the script editor.

Alternatively, run:

```r
source("AutoFilter_LiDAR.R")
```

The `source()` command assumes the script is in your current R working directory. Otherwise, provide its full path.

The script will automatically process the three experiments and export the filtered CSV files.

---

### 6. Find the Filtered CSV Files

After the script finishes, the output folder will be:

```text
~/LidarExperimentData/AutoFiltered/
```

The folder structure will be:

```text
LidarExperimentData/
│
├── Experiment01/
├── Experiment02/
├── Experiment03/
│
└── AutoFiltered/
    ├── Experiment01/
    │   └── Filtered CSV files
    │
    ├── Experiment02/
    │   └── Filtered CSV files
    │
    └── Experiment03/
        └── Filtered CSV files
```

The original CSV files are not modified.

**Note:** The filtering methods identify candidate target measurements using predefined distance or baseline-matching conditions. They do not independently verify that every retained measurement comes from the intended target.

---

### 7. Verify the Installation

To confirm that R, RStudio and the required packages are working correctly, run the following code in the RStudio Console:

```r
# Display R version
R.version.string

# Download and check required packages
install.packages(c("readr", "dplyr", "tidyr", "purrr")) # run once on the machine is enough (it's ok if you run it multiple times)

library(readr)
library(dplyr)
library(tidyr)
library(purrr)

# Test basic R functionality
test <- c(1, 2, 3, 4, 5)

mean(test)
```

Expected result:

```text
[1] 3
```

If the result is `3` and no package-loading errors appear, your R environment is ready.

You can now proceed to the **Automatic LiDAR Data Filtering Using R** section.



### Complete R Script — Automatic LiDAR Filtering

The following R script automatically filters LiDAR CSV files from Experiments 1, 2 and 3.

All exported CSV files will have **`_cleaned`** added before the `.csv` extension.

For example:

- `Experiment01_1m_cardboard.csv` → `Experiment01_1m_cardboard_cleaned.csv`
- `Experiment03_Organza_5cm.csv` → `Experiment03_Organza_5cm_cleaned.csv`

```r
# ============================================================
# AUTOMATIC LiDAR DATA FILTERING
# Experiments 1, 2 and 3
# ============================================================

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
```

### Output Files

After running the script, the filtered CSV files will be saved in:

```text
LidarExperimentData/
└── AutoFiltered/
    ├── Experiment01/
    │   ├── Experiment01_1m_cardboard_cleaned.csv
    │   ├── Experiment01_1m_whiteboard_cleaned.csv
    │   └── ...
    │
    ├── Experiment02/
    │   └── Experiment02_..._cleaned.csv
    │
    └── Experiment03/
        ├── Experiment03_Nomaterial_30cm_cleaned.csv
        ├── Experiment03_Organza_5cm_cleaned.csv
        ├── Experiment03_Polyester_5cm_cleaned.csv
        └── Experiment03_Satin_5cm_cleaned.csv
```

**Note:** The original CSV files remain unchanged. The script automatically excludes previously cleaned files to avoid processing them again.

The distance tolerances for Experiments 1 and 2 are exploratory. Their filtered results may still contain background measurements at similar distances, particularly in Experiment 2. The Experiment 3 filter uses the previously identified baseline region and should be interpreted as selecting baseline-consistent returns rather than independently confirmed cardboard detections.