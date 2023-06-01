# Network-flows: a c++ command line tool for network optimization problems

![c++](https://img.shields.io/badge/C%2B%2B-00599C?style=for-the-badge&logo=c%2B%2B&logoColor=white)
![CMake](https://img.shields.io/badge/CMake-%23008FBA.svg?style=for-the-badge&logo=cmake&logoColor=white)
![Python](https://img.shields.io/badge/python-3670A0?style=for-the-badge&logo=python&logoColor=ffdd54)
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg?style=for-the-badge)](https://opensource.org/licenses/MIT)
![Linux](https://img.shields.io/badge/Linux-FCC624?style=for-the-badge&logo=linux&logoColor=black)

1. [Description](#description)
2. [Project structure](#project-structure)
3. [Algorithms](#algorithms)
4. [How to use](#how-to-use)
5. [Python Tester](#python-tester)

## Description
Command-line solver of the following network flows optimization problems:

1. `Maximum Flow`: it seeks a feasible solution that sends the maximum amount of flow from a specified source note s to node t per unit of time.
2. `Minimum Cost Flow`: it is the most fundamental of all the network flow problems. It searches for the cheapest possible way of sending a certain amount of flow through a flow network.
3.  In particular, the solver solves the `minimum cost maximum flow problem`, seeking the least-cost maximum flow.

## Algorithms
`Maximum Flow`:
- [X] [Edmonds-Karp](https://en.wikipedia.org/wiki/Edmonds%E2%80%93Karp_algorithm)

`Minimum Cost Flow`:
- [X] [Cycle Cancelling Algorithm](https://complex-systems-ai.com/en/maximum-flow-problem/cycle-canceling-algorithm/)
- [X] [Successive Shortest Path Algorithm](https://www.topcoder.com/thrive/articles/Minimum%20Cost%20Flow%20Part%20Two:%20Algorithms)
- [ ] [Primal-Dual Algorithm](https://www.topcoder.com/thrive/articles/Minimum%20Cost%20Flow%20Part%20Two:%20Algorithms)

`Basic algorithms`:
- [X] [BFS](https://www.geeksforgeeks.org/breadth-first-search-or-bfs-for-a-graph/)
- [X] [Bellman-Ford](https://www.geeksforgeeks.org/bellman-ford-algorithm-dp-23/)
- [X] [Dijkstra](https://en.wikipedia.org/wiki/Dijkstra%27s_algorithm)

(*See the implementations [here](src/algorithms)*)

## Project structure
- [data](data): example graphs
- [docs](docs): report of the project and results of the algorithms applied to the graphs inside *data* directory
- [pyTest](pyTest): python tester which permits to easily solve the network flow problems and to **draw a graph using matplotlib**
- [src](src): the command-line tool source files

## How to use
**The following commands are for a generic Linux system, you may need to adapt them depending on your os**

### Requirements
`CMake`: minimum version `3.20`, see [here](https://cmake.org/install/) how to install.

### Use your own graph
Both the c++ command line tool and the Python solver requires an input graph described by a well-formed JSON file. \
**To run the algorithms on you own graph you have to create a JSON file formatted as following**:

```json
{
    "Num_nodes": 5,
    "Edges": [
      {
        "Source": 0,
        "Sink": 1,
        "Capacity": 3,
        "Cost": 1
      },
      {
        "Source": 0,
        "Sink": 2,
        "Capacity": 2,
        "Cost": 1
      },
      {
        "Source": 1,
        "Sink": 2,
        "Capacity": 2,
        "Cost": 1
      },
      {
        "Source": 1,
        "Sink": 3,
        "Capacity": 2,
        "Cost": 1
      },
      {
        "Source": 2,
        "Sink": 3,
        "Capacity": 3,
        "Cost": 1
      },
      {
        "Source": 2,
        "Sink": 4,
        "Capacity": 1,
        "Cost": 1
      },
      {
        "Source": 3,
        "Sink": 4,
        "Capacity": 3,
        "Cost": 1
      }
    ]
 }
```

- `Num_nodes`: number of nodes of the graph;
- `Edges`: JSON array containing all the edges;
- `Source`: source node of the direct edge;
- `Sink`: sink node of the edge;
- `Capacity`: maximum capacity of the edge;
- `Cost`: cost (or weight) per unit flow of the edge,

**Note**:
- The first node (`source`) has index 0;
- The last node (`sink`) has index Num_nodes - 1;
- Each edge must have positive (> 0) `capacity` and `cost`.

See [data](data) directory for more examples.

### Build

1. Clone the repo:
```bash
    git clone git@github.com:LorenzoDrudi/network-flows.git
```

2. Enter the repo:
```bash
    cd network-flows
```
3. Generate project build system:
```bash
    cmake -S . -B build
```
This command creates a build folder containing all the cmake files and the executable.

4. Build the project:
```bash
    cmake --build build
```

### Run
1. After doing the build, enter the build folder:
```bash
  cd build
```
2. Run the project:
```bash
  ./network_flows path/filename.json
```
The argument passed to the executable is the full or relative path of the JSON file of the graph \
(*e.g. `./network_flows ../data/graph1.json`*). \
The filename argument is optional, you can enter it during the execution.

## Python Tester
Inside the [pyTest](pyTest) directory there is a simple python solver developed using [Networkx](https://networkx.org/) library.
The solver permits to:
- draw a graph using `matplotlib`
- solve the maximum flow problem
- solve the minimum cost maximum flow problem

### Requirements:
`Python3`: see [here](https://realpython.com/installing-python/) how to install

### How to use:
**The following commands are for a generic linux system, you may need to adapt them depending on your os**

1. Enter the directory:
```bash
  cd pyTest
```
(*You can ignore the next 2 steps (2, 3) if you want to install Python dependencies locally*)

2. Create a [python virtual environment](https://docs.python.org/3/library/venv.html) where install all the required dependencies:
```bash
  python3 -m venv venv
```

3. Activate the virtual environment:
```bash
  source venv/bin/activate
```

4. Install requirements:
```bash
  pip install -r requirements.txt
```

5. Execute the Python solver:
```bash
  python3 graph_solver.py path/filename.json
  ```
  (e.g. ```python3 graph_solver.py ../data/graph1.json```)

6. Then, when you don't need anymore the python solver, deactivate the virtual environment:
```bash
  deactivate
```
