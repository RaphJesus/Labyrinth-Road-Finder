# Labyrinth Solver

A simple Qt C++ application that finds and visualizes the shortest paths from a single starting point to all exits in a labyrinth. It models the maze as a graph and uses the Breadth-First Search (BFS) algorithm to find the shortest paths.

![Screenshot of the Labyrinth Solver application](image_6ce9c9.png)

## Features

* **File Loading**: Load custom labyrinth maps from `.txt` files.
* **Dual Visualization**: Renders both the labyrinth (grid) and its abstract graph representation side-by-side.
* **BFS Algorithm**: Implements Breadth-First Search to find the shortest paths from start (3) to all exits (2).
* **Dynamic Rendering**: The view is dynamically scaled and centered to fit the application window.
* **Toggleable Views**: Use the toolbar buttons to toggle the visibility of:
    * Labyrinth grid
    * Labyrinth paths
    * Abstract graph
    * Graph paths

## Project Structure

This project is organized into a clean `src/` directory, with data files separated.

Tema2/ ├── .gitignore ├── README.md ├── Tema2.pro ├── data/ │ ├── labirint.txt │ └── labirint2.txt └── src/ ├── labyrinth.cpp ├── labyrinth.h ├── labyrinthgraph.cpp ├── labyrinthgraph.h ├── labyrinthrenderer.cpp ├── labyrinthrenderer.h ├── main.cpp ├── mainwindow.cpp ├── mainwindow.h ├── mainwindow.ui ├── pathsolver.cpp └── pathsolver.h


### Core Classes

* **`Labyrinth`**: Handles loading, storing, and accessing the raw maze matrix data.
* **`LabyrinthGraph`**: Responsible for building the adjacency list (graph) from a `Labyrinth` object.
* **`PathSolver`**: Implements the BFS algorithm and path reconstruction logic.
* **`LabyrinthRenderer`**: Contains all static `paintEvent` logic for drawing the maze, graph, and paths.
* **`MainWindow`**: Acts as the main controller, handling UI events (button clicks, file opening) and coordinating the other classes.

## How to Build

### Dependencies

* **Qt 5** or **Qt 6** (Core, Gui, Widgets)
* A C++ compiler (g++, MSVC, Clang)

### Steps

1.  Clone the repository.
2.  Open a terminal in the project's root directory.
3.  Run `qmake` (or `qmake6` for Qt 6):
    ```sh
    qmake Tema2.pro
    ```
4.  Run `make` (or `nmake` on Windows with MSVC):
    ```sh
    make
    ```
5.  Run the resulting executable (e.g., `Tema2`, `Tema2.exe`, or from the `debug/` / `release/` folder).

## Input File Format

The application reads a simple `.txt` file representing the maze.

* `0`: Represents a wall (impassable).
* `1`: Represents a path (passable).
* `2`: Represents an exit point.
* `3`: Represents the single starting point.

### Example (`data/labirint.txt`)

000002 211112 003000 101101 200111 111100