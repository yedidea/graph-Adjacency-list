<!-- Email: yedidea9@gmail.com -->

# Graph Assignment

This project implements an undirected weighted graph in C++ using an adjacency list.

The project does not use STL containers such as `vector`, `stack`, `queue`, or `priority_queue`.
All needed data structures are implemented manually using dynamic arrays and linked lists.

## Project Structure

### Graph

The `Graph` class represents an undirected weighted graph.

The graph is initialized with a fixed number of vertices, and this number cannot be changed after creation.

The graph is implemented using an adjacency list.
Each vertex has a linked list of its neighbors, and each edge stores the destination vertex and the edge weight.

Main functions:

* `Graph(int vertices)` - creates a graph with a fixed number of vertices.
* `Graph(const Graph& other)` - copy constructor, creates a deep copy of another graph.
* `operator=` - assignment operator, copies one graph into another using deep copy.
* `~Graph()` - destructor, releases all dynamically allocated memory.
* `addEdge(int src, int dest, int weight = 1)` - adds an undirected weighted edge to the graph.
* `removeEdge(int src, int dest)` - removes an edge from the graph. If the edge does not exist, an exception is thrown.
* `print_graph(const char* title = "Graph")` - prints the graph in a clear format, including an adjacency matrix and a list of edges.
* `getVertices()` - returns the number of vertices in the graph.
* `getNeighbors(int vertex)` - returns the adjacency list of a given vertex.
* `edgeExists(int src, int dest)` - checks if an edge exists between two vertices.
* `getWeight(int src, int dest)` - returns the weight of an edge. If the edge does not exist, an exception is thrown.
* `getEdgeCount()` - returns the number of undirected edges in the graph.
* `getTotalWeight()` - returns the total weight of all undirected edges in the graph.

The class also uses private helper functions for input validation, copying data, deleting allocated memory, and adding or removing directed edges inside the adjacency list.

### Algorithms

The `Algorithms` class contains graph algorithms that work on the `Graph` class.

Implemented algorithms:

* `bfs` - returns a BFS tree from a given source vertex.
* `dfs` - returns a DFS tree or forest with only tree edges.
* `dijkstra` - returns a shortest paths tree from a given source vertex.
* `prim` - returns a minimum spanning tree.
* `kruskal` - returns a minimum spanning tree.

### Additional Data Structures

Since STL containers are not used, the project also includes basic implementations of:

* `Queue` - used for BFS.
* `PriorityQueue` - used for Dijkstra and Prim.
* `UnionFind` - used for Kruskal.

The priority queue supports `push`, `popMin`, `contains`, and `decreaseKey`.
The `decreaseKey` function is implemented with a simple linear search.

## Files

* `Graph.hpp`, `Graph.cpp` - graph implementation.
* `Algorithms.hpp`, `Algorithms.cpp` - graph algorithms.
* `Queue.hpp`, `Queue.cpp` - simple queue implementation.
* `PriorityQueue.hpp`, `PriorityQueue.cpp` - simple priority queue implementation.
* `UnionFind.hpp`, `UnionFind.cpp` - union find implementation.
* `main.cpp` - demonstration of the project.
* `test.cpp` - unit tests using doctest.
* `doctest.h` - testing library.
* `Makefile` - build and run commands.

## How to Run

Run the main demonstration:

```bash
make Main
```

Run the unit tests:

```bash
make test
```

Run Valgrind memory check:

```bash
make valgrind
```

Clean compiled files:

```bash
make clean
```

## Memory Management

The project uses dynamic memory allocation, so memory management is handled manually.

The Graph, Queue, PriorityQueue, and UnionFind classes include destructors to release allocated memory.
The Graph class also implements a copy constructor and assignment operator in order to support deep copy and avoid memory issues.

The project was tested with Valgrind to check for memory leaks.

## Testing

The project includes unit tests for the graph operations, algorithms, and helper data structures.

The tests check edge insertion and removal, invalid input, exceptions, deep copy behavior, BFS, DFS, Dijkstra, Prim, Kruskal, Queue, PriorityQueue, and UnionFind.
