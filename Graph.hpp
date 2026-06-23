// Email: yedidea9@gmail.com
#ifndef GRAPH_HPP
#define GRAPH_HPP

namespace graph {

struct EdgeNode {
    int dest;
    int weight;
    EdgeNode* next;
};

class Graph {
private:
    int vertices;
    EdgeNode** adjacencyList;

    void validateVertex(int vertex) const;
    void clear();
    void copyFrom(const Graph& other);
    bool addDirectedEdge(int src, int dest, int weight);
    bool removeDirectedEdge(int src, int dest);

public:
    Graph(int vertices);
    Graph(const Graph& other);
    Graph& operator=(const Graph& other);
    ~Graph();

    void addEdge(int src, int dest, int weight = 1);
    void removeEdge(int src, int dest);
    void print_graph(const char* title = "Graph") const;

    int getVertices() const;
    const EdgeNode* getNeighbors(int vertex) const;
    bool edgeExists(int src, int dest) const;
    int getWeight(int src, int dest) const;
    int getEdgeCount() const;
    int getTotalWeight() const;
};

}

#endif
