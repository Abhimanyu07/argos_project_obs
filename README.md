# Collective Robotics Tutorial 2 - Robot Behaviors and Swarm Systems

This project contains ARGoS3 experiments, recorded stop-and-go data, analysis
plots, screenshots, and a demo video for the behaviors required in Tutorial 2:

- obstacle avoidance
- wall following
- vacuum-cleaner style movement
- stop-and-go swarm aggregation

## Requirements

- Linux environment with ARGoS3 installed
- CMake
- C++ compiler with C++17 support
- Lua 5.1 development files
- Python 3 with Jupyter and Matplotlib for the data-analysis notebook

This project was tested with:

```bash
argos3 --version
```

If ARGoS3 is not installed, download the package for your operating system from the official ARGoS website:

```text
https://www.argos-sim.info/core.php
```

On Ubuntu, after downloading the `.deb` package, install it from the download directory with:

```bash
sudo apt install ./argos3_simulator-*.deb
```

After installation, make sure this command works:

```bash
argos3 --version
```

## Build

From the project root, `argos_project_obs/`:

```bash
mkdir -p build
cd build
cmake ..
make
```

Return to the project root before running the experiments:

```bash
cd ..
```

The build should create:

```text
build/libswarm_controller.so
```

## Run Experiments

Run each experiment from the project root, `argos_project_obs/`, using
`argos3 -c`.

Obstacle avoidance:

```bash
argos3 -c experiments/obstacle_avoidance.argos
```

Wall follower:

```bash
argos3 -c experiments/wall_follower.argos
```

Vacuum cleaner behavior:

```bash
argos3 -c experiments/cleaner.argos
```

Stop-and-go swarm behavior:

```bash
argos3 -c experiments/stop_and_go.argos
```

To run an experiment without the graphical visualization:

```bash
argos3 -c experiments/stop_and_go.argos -z
```

## Stop-and-Go Data

The stop-and-go experiment uses `loop_functions/data_handle.cpp` to write the
latest simulation run to the project root:

```text
stop_and_go_data.csv
```

The loop function is intentionally left this way. After a run, archive the CSV
manually in `data_stop_and_go/` if it should be kept as part of the analysis
dataset, for example:

```bash
mv stop_and_go_data.csv data_stop_and_go/stop_and_go_dataW.csv
```

The included labeled files, such as `stop_and_go_dataA.csv` through
`stop_and_go_dataV.csv`, are stored in `data_stop_and_go/`. The file
`stop_go_exp_config.csv` lists the parameter settings and CSV filename for each
recorded run.

## Data Analysis

The analysis notebook is stored in:

```text
data_analysis/stop_and_go_analysis.ipynb
```

Run it from the project root so the notebook can find `stop_go_exp_config.csv`
and the archived CSV files in `data_stop_and_go/`:

```bash
cd argos_project_obs
python3 -m pip install jupyter matplotlib
jupyter notebook data_analysis/stop_and_go_analysis.ipynb
```

In Jupyter, open the notebook and run all cells. The notebook reads the
stop-and-go CSV files, computes summary metrics, and writes generated figures to:

```text
graphics/plots/
```



## Results and Media

Generated visual results are grouped under `graphics/`:

```text
graphics/video/demo_video.mp4              Demo MP4 video of the project run
graphics/experiment_screenshots/           Screenshots captured from ARGoS runs
graphics/plots/all_runs_summary.png        Summary plot across recorded runs
graphics/plots/convergence_by_swarm_size.png
graphics/plots/100_robot_parameter_comparison.png
graphics/plots/stable_run_H.png
graphics/plots/stable_run_T.png
```

The screenshots and plots document the observed experiment behavior and the
stop-and-go parameter analysis.

## Project Structure

```text
controllers/                         Robot controller source files
experiments/                         ARGoS experiment configuration files
loop_functions/                      Data collection loop function
data_analysis/                       Jupyter notebook for stop-and-go analysis
data_stop_and_go/                    Archived labeled stop-and-go CSV runs
graphics/
  experiment_screenshots/            Captured experiment screenshots
  plots/                             Generated analysis plots
  video/                             Demo video output
build/                               Generated CMake build output
report.md, report.pdf                Project report files
stop_go_exp_config.csv               Stop-and-go run configuration table
stop_and_go_data.csv                 Latest generated stop-and-go run
```
