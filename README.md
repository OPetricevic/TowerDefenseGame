# Tower Defense Game

A simple Tower Defense game built using **C++** and **SFML** (Simple and Fast Multimedia Library).

## Description

This game is a classic **Tower Defense** genre where players place towers on a grid to stop waves of enemies from reaching their goal. Players can place towers that will automatically shoot at enemies moving along a predefined path. The goal is to prevent the enemies from reaching the end of the path by strategically placing towers on the grid.

**Current State**:  
The game is still a work in progress. At the moment, it only features the enemies walking towards the end of the path and the ability to place towers on the grid. No actual combat mechanics have been implemented yet.

## Features

- **Enemy AI**: Enemies walk towards the end of a predefined path.
- **Tower Placement**: Players can place towers on the grid, avoiding the path of enemies and preventing them from being placed too close to other towers.
- **Basic Grid System**: A simple grid layout for the game map.

## Installation

### Prerequisites

To build and run this game, you need the following dependencies:

- **C++17** (or later)
- **SFML** (for graphics, window management, and events)
- **SQLite3** (for storing and retrieving level data)

You can install these libraries on most Linux systems using the following commands:

```bash
sudo apt-get install libsfml-dev
sudo apt-get install libsqlite3-dev
