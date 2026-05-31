# Collective Robotics Task 2

This project contains ARGoS3 experiments for the behaviors required in Task 2:

- obstacle avoidance
- wall following
- vacuum-cleaner style movement
- stop-and-go swarm aggregation

## Requirements

- Linux environment with ARGoS3 installed
- CMake
- C++ compiler with C++17 support
- Lua 5.1 development files

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

From the project root:

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

Run each experiment from the project root using `argos3 -c`.

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

The stop-and-go experiment uses loop functions to write simulation data to:

```text
stop_and_go_data.csv
```

The included `stop_and_go_data*.csv` files are recorded runs from different stop-and-go experiment configurations. The file `stop_go_exp_config.csv` lists the parameter settings used for those recorded runs.

## Project Structure

```text
controllers/       Robot controller source files
experiments/       ARGoS experiment configuration files
loop_functions/    Data collection loop function
build/             Generated build output
```

