# Philosophers Dining Problem

This project simulates the classic "Dining Philosophers Problem" using multithreading in C. The simulation involves philosophers who alternately think, eat, and sleep, while sharing forks with their neighbors.

## Table of Contents

- [Philosophers Dining Problem](#philosophers-dining-problem)
  - [Table of Contents](#table-of-contents)
  - [Getting Started](#getting-started)
    - [Prerequisites](#prerequisites)
    - [Building the Project](#building-the-project)
    - [Running the Simulation](#running-the-simulation)
  - [Project Structure](#project-structure)
  - [Files Description](#files-description)
  - [Contributing](#contributing)
  - [License](#license)

## Getting Started

### Prerequisites

- GCC (GNU Compiler Collection)
- Make
- pthread library

### Building the Project

To build the project, run the following command:

```bash
make
```

### Running the Simulation

To run the simulation, execute the following command:

```bash
./philo [number_of_philosophers] time_to_die time_to_eat time_to_sleep  number_of_times_each_philosopher_must_eat 
```

- `time_to_die`: The time in milliseconds after which a philosopher dies if they have not started eating.
- `time_to_eat`: The time in milliseconds that a philosopher takes to eat.
- `time_to_sleep`: The time in milliseconds that a philosopher takes to sleep.
- `number_of_times_each_philosopher_must_eat`: The number of times each philosopher must eat before the simulation ends.
- `number_of_philosophers`: The number of philosophers.

## Project Structure

```
.vscode/
    launch.json
    settings.json
philo/
    check_eats.c
    main.c
    Makefile
    monitor.c
    parsing.c
    philo.h
    routine.c
    time.c
    utils.c
README.md
```

## Files Description

- `check_eats.c`: Contains functions to check if all philosophers have eaten the required number of times.
- `main.c`: The main file that contains the entry point of the program.
- `Makefile`: Contains the build instructions for the project.
- `monitor.c`: Contains functions to monitor the philosophers.
- `parsing.c`: Contains functions to parse the command-line arguments.
- `philo.h`: Contains the function prototypes and global variables.
- `routine.c`: Contains the main routine of the philosophers.
- `time.c`: Contains functions to get the current time.
- `utils.c`: Contains utility functions.

## useful links

- [Oceano Likns](https://suspectedoceano.notion.site/Philosophers-b1bf3c57eee6420cafa7d0900b3d3216)

## Contributing

Any contributions you make are **greatly appreciated**. Thank youu!