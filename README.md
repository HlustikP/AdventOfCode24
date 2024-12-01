# Advent of Code C++23 Solutions 2024
This repository contains my solutions for the [Advent of Code 2024](https://adventofcode.com/2024) challenges.

In accordance to the [Advent of Code Author's request](https://adventofcode.com/2024/about),
I am not including any input files, please provide them yourself
inside the `src/inputs` directory.

## Requirements
- CMake
- C++20 compatible compiler
- Ninja [(Get here)](https://ninja-build.org)

## Build
```bash
cmake --preset x64-release
cd ./build/x64-release
ninja
```

## Run
`AdventOfCode24.exe path/to/iputs/dir day` so e.g.:
```bash
AdventOfCode24.exe ./src/inputs 1
```

Inputs are expected to be in theformat `inputDAY-TASK.txt` so e.g. `input1-1.txt`.
