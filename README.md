# Graph and Network Algorithms

## Project Description

This repository contains implementations of selected graph algorithms and PERT network analysis in C++. The project demonstrates methods for finding shortest paths, minimum spanning trees, Eulerian cycles, Hamiltonian paths, and solving the Traveling Salesman Problem (TSP), as well as managing task schedules using PERT.

---

## Implemented Algorithms

### Graph Algorithms (`Graf.cpp`)

| Category           | Algorithms / Methods                                      |
| ------------------ | --------------------------------------------------------- |
| Traversal          | BFS (Breadth-First Search), DFS (cycle detection)         |
| Shortest Paths     | Dijkstra, A\* (A-star)                                    |
| MST                | Prim's Algorithm                                          |
| TSP                | Christofides Algorithm: MST + Matching + Euler + Shortcut |
| Eulerian Cycle     | Hierholzer's Algorithm                                    |
| Hamiltonian Path   | Shortcut of Eulerian Cycle                                |
| Graph Connectivity | `isConnected()` (based on BFS and optional undirection)   |

### PERT Network Analysis (`PERTGraph.cpp` + `main.cpp`)

* Adding activities with 3-point estimates (a, m, b)
* Calculating expected duration (TE) and variance
* Topological sorting of the task graph
* Computing:

  * ES (Early Start)
  * EF (Early Finish)
  * LS (Late Start)
  * LF (Late Finish)
  * Slack (float time)
* Identifying the critical path
* Exporting data to `GANTT.csv`
* Generating a Gantt chart highlighting critical activities and slack time (`generate_gantt.py`)

---

## ⚙️ Build and Run

```bash
cmake -B ./build -S ./
cd build
make
./bin/B01_app
```

Running the application will generate `GANTT.csv` and a `GANTT.png` chart.
Make sure the Python path in `PERTGraph.cpp` is correct:
> ```cpp
> std::string pythonPath = "\"C:\\Program Files\\Python39\\python.exe\"";
> ```

---

## Directory Structure

* `source/` – source files `.cpp`
* `include/` – header files `.h`
* `build/bin/` – compiled executables
* `GANTT.csv`, `GANTT.png` – schedule data and Gantt chart

---

## License

Educational project. You are free to use and modify the code for learning and teaching purposes.

---

## Author

Repository created by **KmazuR-afk** as part of the *Badania operacyjne* course.

---

If you have questions about the code or want to extend the project with new algorithms – feel free to reach out or fork the repository!
