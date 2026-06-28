// Email: yedidea9@gmail.com
#include "Algorithms.hpp"
#include "Queue.hpp"
#include "PriorityQueue.hpp"
#include "UnionFind.hpp"
#include <stdexcept>

namespace graph {

/**
 * Helper structure used by Kruskal's algorithm.
 * It stores one undirected edge as source, destination, and weight.
 */
struct EdgeData {
    int src;
    int dest;
    int weight;
};

/**
 * A large value used as "infinity" for Dijkstra and Prim.
 */
static const int INF = 1000000000;

/**
 * Runs BFS from a given source vertex.
 *
 * The function uses the custom Queue class and returns a new graph that
 * contains only the tree edges discovered by the BFS traversal.
 */
Graph Algorithms::bfs(const Graph& input, int source) {
    int vertices = input.getVertices();
    if (source < 0 || source >= vertices) {
        throw std::out_of_range("BFS source is out of range");
    }

    Graph result(vertices);
    bool* visited = new bool[vertices];

    for (int i = 0; i < vertices; i++) {
        visited[i] = false;
    }

    Queue queue(vertices);
    visited[source] = true;
    queue.enqueue(source);

    while (!queue.isEmpty()) {
        int currentVertex = queue.dequeue();
        const EdgeNode* neighbor = input.getNeighbors(currentVertex);

        while (neighbor != 0) {
            int nextVertex = neighbor->dest;

            if (!visited[nextVertex]) {
                visited[nextVertex] = true;
                result.addEdge(currentVertex, nextVertex, neighbor->weight);
                queue.enqueue(nextVertex);
            }

            neighbor = neighbor->next;
        }
    }

    delete[] visited;
    return result;
}

/**
 * Recursive helper for DFS.
 * It marks the current vertex and adds only tree edges to the result graph.
 */
void Algorithms::dfsVisit(const Graph& input, Graph& result, int vertex, bool* visited) {
    visited[vertex] = true;

    const EdgeNode* neighbor = input.getNeighbors(vertex);
    while (neighbor != 0) {
        int nextVertex = neighbor->dest;

        if (!visited[nextVertex]) {
            result.addEdge(vertex, nextVertex, neighbor->weight);
            dfsVisit(input, result, nextVertex, visited);
        }

        neighbor = neighbor->next;
    }
}

/**
 * Runs DFS from a given start vertex.
 *
 * After visiting the connected component of the start vertex, the function
 * continues with unvisited vertices so the result can be a DFS forest.
 */
Graph Algorithms::dfs(const Graph& input, int start) {
    int vertices = input.getVertices();
    if (start < 0 || start >= vertices) {
        throw std::out_of_range("DFS start vertex is out of range");
    }

    Graph result(vertices);
    bool* visited = new bool[vertices];

    for (int i = 0; i < vertices; i++) {
        visited[i] = false;
    }

    dfsVisit(input, result, start, visited);

    for (int i = 0; i < vertices; i++) {
        if (!visited[i]) {
            dfsVisit(input, result, i, visited);
        }
    }

    delete[] visited;
    return result;
}

/**
 * Runs Dijkstra's algorithm from a given source vertex.
 *
 * The function uses the custom PriorityQueue. The priority is the current
 * shortest known distance from the source. The returned graph contains the
 * parent edges that form the shortest paths tree.
 */
Graph Algorithms::dijkstra(const Graph& input, int source) {
    int vertices = input.getVertices();
    if (source < 0 || source >= vertices) {
        throw std::out_of_range("Dijkstra source is out of range");
    }

    int* dist = new int[vertices];
    int* parent = new int[vertices];
    bool* visited = new bool[vertices];

    for (int i = 0; i < vertices; i++) {
        dist[i] = INF;
        parent[i] = -1;
        visited[i] = false;
    }

    dist[source] = 0;

  
    PriorityQueue queue(vertices);
    queue.push(source, 0);

    while (!queue.isEmpty()) {
        PQItem item = queue.popMin();
        int currentVertex = item.vertex;

        if (visited[currentVertex]) {
            continue;
        }

        visited[currentVertex] = true;

        const EdgeNode* neighbor = input.getNeighbors(currentVertex);
        while (neighbor != 0) {
            int nextVertex = neighbor->dest;
            int weight = neighbor->weight;

            if (weight < 0) {
                delete[] dist;
                delete[] parent;
                delete[] visited;
                throw std::invalid_argument("Dijkstra cannot run on negative weights");
            }

            if (!visited[nextVertex] && dist[currentVertex] != INF &&
                dist[currentVertex] + weight < dist[nextVertex]) {
                dist[nextVertex] = dist[currentVertex] + weight;
                parent[nextVertex] = currentVertex;

                if (queue.contains(nextVertex)) {
                    queue.decreaseKey(nextVertex, dist[nextVertex]);
                } else {
                    queue.push(nextVertex, dist[nextVertex]);
                }
            }

            neighbor = neighbor->next;
        }
    }

    Graph result(vertices);
    for (int vertex = 0; vertex < vertices; vertex++) {
        if (parent[vertex] != -1) {
            int weight = input.getWeight(parent[vertex], vertex);
            result.addEdge(parent[vertex], vertex, weight);
        }
    }

    delete[] dist;
    delete[] parent;
    delete[] visited;
    return result;
}

/**
 * Runs Prim's algorithm to find a minimum spanning tree.
 *
 * The priority queue stores the cheapest known edge that can connect each
 * vertex to the current tree. If the graph is not connected, no MST exists.
 */
Graph Algorithms::prim(const Graph& input) {
    int vertices = input.getVertices();

    int* key = new int[vertices];
    int* parent = new int[vertices];
    bool* inMST = new bool[vertices];

    for (int i = 0; i < vertices; i++) {
        key[i] = INF;
        parent[i] = -1;
        inMST[i] = false;
    }

    key[0] = 0;


    PriorityQueue queue(vertices);
    queue.push(0, 0);

    int selectedVertices = 0;

    while (!queue.isEmpty() && selectedVertices < vertices) {
        PQItem item = queue.popMin();
        int currentVertex = item.vertex;

        if (inMST[currentVertex]) {
            continue;
        }

        inMST[currentVertex] = true;
        selectedVertices++;

        const EdgeNode* neighbor = input.getNeighbors(currentVertex);
        while (neighbor != 0) {
            int nextVertex = neighbor->dest;
            int weight = neighbor->weight;

            if (!inMST[nextVertex] && weight < key[nextVertex]) {
                key[nextVertex] = weight;
                parent[nextVertex] = currentVertex;

                if (queue.contains(nextVertex)) {
                    queue.decreaseKey(nextVertex, key[nextVertex]);
                } else {
                    queue.push(nextVertex, key[nextVertex]);
                }
            }

            neighbor = neighbor->next;
        }
    }

    if (selectedVertices != vertices) {
        delete[] key;
        delete[] parent;
        delete[] inMST;
        throw std::runtime_error("Graph is not connected, MST does not exist");
    }

    Graph result(vertices);
    for (int vertex = 1; vertex < vertices; vertex++) {
        if (parent[vertex] == -1) {
            delete[] key;
            delete[] parent;
            delete[] inMST;
            throw std::runtime_error("Graph is not connected, MST does not exist");
        }

        result.addEdge(parent[vertex], vertex, key[vertex]);
    }

    delete[] key;
    delete[] parent;
    delete[] inMST;
    return result;
}

/**
 * Sorts an array of edges by weight using selection sort.
 * This simple implementation is enough because the assignment does not require
 * a specific time complexity for the helper data structures.
 */
static void sortEdgesByWeight(EdgeData* edges, int edgeCount) {
    for (int i = 0; i < edgeCount - 1; i++) {
        int minIndex = i;

        for (int j = i + 1; j < edgeCount; j++) {
            if (edges[j].weight < edges[minIndex].weight) {
                minIndex = j;
            }
        }

        if (minIndex != i) {
            EdgeData temp = edges[i];
            edges[i] = edges[minIndex];
            edges[minIndex] = temp;
        }
    }
}

/**
 * Runs Kruskal's algorithm to find a minimum spanning tree.
 *
 * The function collects all undirected edges, sorts them by weight, and uses
 * UnionFind to avoid adding edges that would create cycles.
 */
Graph Algorithms::kruskal(const Graph& input) {
    int vertices = input.getVertices();
    int maxEdges = vertices * (vertices - 1) / 2;
    EdgeData* edges = new EdgeData[maxEdges];
    int edgeCount = 0;

    for (int src = 0; src < vertices; src++) {
        const EdgeNode* neighbor = input.getNeighbors(src);
        while (neighbor != 0) {
            if (src < neighbor->dest) {
                edges[edgeCount].src = src;
                edges[edgeCount].dest = neighbor->dest;
                edges[edgeCount].weight = neighbor->weight;
                edgeCount++;
            }
            neighbor = neighbor->next;
        }
    }

    sortEdgesByWeight(edges, edgeCount);

    Graph result(vertices);
    UnionFind sets(vertices);
    int selectedEdges = 0;

    for (int i = 0; i < edgeCount && selectedEdges < vertices - 1; i++) {
        int src = edges[i].src;
        int dest = edges[i].dest;

        if (!sets.connected(src, dest)) {
            sets.unite(src, dest);
            result.addEdge(src, dest, edges[i].weight);
            selectedEdges++;
        }
    }

    delete[] edges;

    if (selectedEdges != vertices - 1) {
        throw std::runtime_error("Graph is not connected, MST does not exist");
    }

    return result;
}

}
