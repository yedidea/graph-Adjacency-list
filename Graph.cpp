// Email: yedidea9@gmail.com
#include "Graph.hpp"
#include <iostream>
#include <stdexcept>

namespace graph {

Graph::Graph(int vertices) : vertices(vertices), adjacencyList(0) {
    if (vertices <= 0) {
        throw std::invalid_argument("Number of vertices must be positive");
    }

    adjacencyList = new EdgeNode*[vertices];
    for (int i = 0; i < vertices; i++) {
        adjacencyList[i] = 0;
    }
}

Graph::Graph(const Graph& other) : vertices(0), adjacencyList(0) {
    copyFrom(other);
}

Graph& Graph::operator=(const Graph& other) {
    if (this != &other) {
        clear();
        copyFrom(other);
    }
    return *this;
}

Graph::~Graph() {
    clear();
}

void Graph::validateVertex(int vertex) const {
    if (vertex < 0 || vertex >= vertices) {
        throw std::out_of_range("Vertex index is out of range");
    }
}

void Graph::clear() {
    if (adjacencyList == 0) {
        return;
    }

    for (int i = 0; i < vertices; i++) {
        EdgeNode* current = adjacencyList[i];
        while (current != 0) {
            EdgeNode* next = current->next;
            delete current;
            current = next;
        }
    }

    delete[] adjacencyList;
    adjacencyList = 0;
    vertices = 0;
}

void Graph::copyFrom(const Graph& other) {
    vertices = other.vertices;
    adjacencyList = new EdgeNode*[vertices];

    for (int i = 0; i < vertices; i++) {
        adjacencyList[i] = 0;

        const EdgeNode* current = other.adjacencyList[i];
        EdgeNode* tail = 0;

        while (current != 0) {
            EdgeNode* newNode = new EdgeNode;
            newNode->dest = current->dest;
            newNode->weight = current->weight;
            newNode->next = 0;

            if (adjacencyList[i] == 0) {
                adjacencyList[i] = newNode;
            } else {
                tail->next = newNode;
            }

            tail = newNode;
            current = current->next;
        }
    }
}

bool Graph::addDirectedEdge(int src, int dest, int weight) {
    EdgeNode* current = adjacencyList[src];

    while (current != 0) {
        if (current->dest == dest) {
            current->weight = weight;
            return false;
        }
        current = current->next;
    }

    EdgeNode* newNode = new EdgeNode;
    newNode->dest = dest;
    newNode->weight = weight;
    newNode->next = adjacencyList[src];
    adjacencyList[src] = newNode;
    return true;
}

bool Graph::removeDirectedEdge(int src, int dest) {
    EdgeNode* current = adjacencyList[src];
    EdgeNode* previous = 0;

    while (current != 0) {
        if (current->dest == dest) {
            if (previous == 0) {
                adjacencyList[src] = current->next;
            } else {
                previous->next = current->next;
            }

            delete current;
            return true;
        }

        previous = current;
        current = current->next;
    }

    return false;
}

void Graph::addEdge(int src, int dest, int weight) {
    validateVertex(src);
    validateVertex(dest);

    if (src == dest) {
        throw std::invalid_argument("Self loops are not supported in this assignment");
    }

    if (weight < 0) {
        throw std::invalid_argument("Negative edge weights are not supported");
    }

    addDirectedEdge(src, dest, weight);
    addDirectedEdge(dest, src, weight);
}

void Graph::removeEdge(int src, int dest) {
    validateVertex(src);
    validateVertex(dest);

    bool removedFromSrc = removeDirectedEdge(src, dest);
    bool removedFromDest = removeDirectedEdge(dest, src);

    if (!removedFromSrc || !removedFromDest) {
        throw std::runtime_error("Edge does not exist");
    }
}

void Graph::print_graph(const char* title) const {
    std::cout << "\n==================== " << title << " ====================" << std::endl;
    std::cout << std::endl;

    std::cout << std::endl;
    std::cout << "Adjacency Matrix" << std::endl;
    std::cout << "------------------------------------------------" << std::endl;

    std::cout << "      ";
    for (int i = 0; i < vertices; i++) {
        if (i < 10) {
            std::cout << "   " << i;
        } else {
            std::cout << "  " << i;
        }
    }
    std::cout << std::endl;

    std::cout << "    ";
    for (int i = 0; i < vertices; i++) {
        std::cout << "----";
    }
    std::cout << "-" << std::endl;

    for (int i = 0; i < vertices; i++) {
        if (i < 10) {
            std::cout << "  " << i << " |";
        } else {
            std::cout << " " << i << " |";
        }

        for (int j = 0; j < vertices; j++) {
            if (edgeExists(i, j)) {
                int weight = getWeight(i, j);

                if (weight < 10) {
                    std::cout << "   " << weight;
                } else if (weight < 100) {
                    std::cout << "  " << weight;
                } else {
                    std::cout << " " << weight;
                }
            } else {
                std::cout << "   .";
            }
        }

        std::cout << std::endl;
    }

    std::cout << std::endl;
    std::cout << "Edges" << std::endl;
    std::cout << "------------------------------------------------" << std::endl;

    bool foundEdge = false;

    for (int i = 0; i < vertices; i++) {
        const EdgeNode* current = adjacencyList[i];

        while (current != 0) {
            // The graph is undirected, so every edge is stored twice.
            // We print only i < dest to avoid duplicate edges.
            if (i < current->dest) {
                std::cout << i << " -- " << current->dest
                          << "    weight = " << current->weight << std::endl;
                foundEdge = true;
            }

            current = current->next;
        }
    }

    if (!foundEdge) {
        std::cout << "No edges" << std::endl;
    }

    std::cout << "================================================" << std::endl;
}

int Graph::getVertices() const {
    return vertices;
}

const EdgeNode* Graph::getNeighbors(int vertex) const {
    validateVertex(vertex);
    return adjacencyList[vertex];
}

bool Graph::edgeExists(int src, int dest) const {
    validateVertex(src);
    validateVertex(dest);

    const EdgeNode* current = adjacencyList[src];
    while (current != 0) {
        if (current->dest == dest) {
            return true;
        }
        current = current->next;
    }

    return false;
}

int Graph::getWeight(int src, int dest) const {
    validateVertex(src);
    validateVertex(dest);

    const EdgeNode* current = adjacencyList[src];
    while (current != 0) {
        if (current->dest == dest) {
            return current->weight;
        }
        current = current->next;
    }

    throw std::runtime_error("Edge does not exist");
}

int Graph::getEdgeCount() const {
    int directedCount = 0;

    for (int i = 0; i < vertices; i++) {
        const EdgeNode* current = adjacencyList[i];
        while (current != 0) {
            directedCount++;
            current = current->next;
        }
    }

    return directedCount / 2;
}

int Graph::getTotalWeight() const {
    int sum = 0;

    for (int i = 0; i < vertices; i++) {
        const EdgeNode* current = adjacencyList[i];
        while (current != 0) {
            if (i < current->dest) {
                sum += current->weight;
            }
            current = current->next;
        }
    }

    return sum;
}

}
