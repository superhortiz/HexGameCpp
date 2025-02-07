# HexGameCpp
A C++ implementation of the game Hex, featuring a Monte Carlo AI opponent.

## Introduction

HexGameCpp is a C++ implementation of the classic strategy game Hex.  The game is played on a hexagonal grid, and the goal is for each player to connect their two opposite sides of the board with a path of their stones. This version includes a computer AI opponent that uses a Monte Carlo simulation to choose its moves.

## How to Play

The rules of Hex are simple:

1. The game is played on a hexagonal grid.
2. Two players take turns placing their stones on empty hexagons.
3. The goal is to connect your two opposite sides of the board with a continuous path of your stones.  Red tries to connect North and South. Blue tries to connect East and West.
4. The first player to connect their sides wins.

In this implementation:

* You can choose to play as either Blue or Red.
* The computer plays as the opposite color.
* The game continues until one player wins.

## Build Instructions

1. Make sure you have a C++ compiler (like g++) installed on your system.
2. Clone this repository.
3. Navigate to the project directory.
4. Use `make` to build the game: `make hexgame`

## Features

* Implements the core logic of the game Hex.
* Includes a Monte Carlo AI opponent for single-player mode.
* Supports variable board sizes.
* Clear console-based interface.

## Dependencies

* A C++ compiler (e.g., g++).  No other external libraries are strictly required for the core game.

## How to Run

1. After building the game using the instructions above, you can run the executable: `./hexgame` (Linux/macOS) or `hexgame.exe` (Windows).
2. Follow the prompts in the console to select your color and make your moves.
