// Email: yedidea9@gmail.com
#include "Graph.hpp"
#include <iostream>
#include <stdexcept>

namespace graph {

/**
 * Creates a graph with a fixed number of vertices.
 * Each vertex starts with an empty adjacency list.
 */
Graph::Graph(int vertices) : vertices(vertices), adjacencyList(0) {
    if (vertices <= 0) {
        throw std::invalid_argument("Number of vertices must be positive");
    }

    adjacencyList = new EdgeNode*[vertices];
    for (int i = 0; i < vertices; i++) {
        adjacencyList[i] = 0;
    }
}

/**
 * Copy constructor.
 * Creates a deep copy so the new graph owns its own adjacency lists.
 */
Graph::Graph(const Graph& other) : vertices(0), adjacencyList(0) {
    copyFrom(other);
}

/**
 * Assignment operator.
 * Clears the current graph and then creates a deep copy of the other graph.
 */
Graph& Graph::operator=(const Graph& other) {
    if (this != &other) {
        clear();
        copyFrom(other);
    }
    return *this;
}

/**
 * Destructor.
 * Frees all dynamically allocated memory used by the adjacency list.
 */
Graph::~Graph() {
    clear();
}

/**
 * Checks that a vertex index is inside the valid range of the graph.
 */
void Graph::validateVertex(int vertex) const {
    if (vertex < 0 || vertex >= vertices) {
        throw std::out_of_range("Vertex index is out of range");
    }
}

/**
 * Deletes all adjacency lists and resets the graph fields.
 * This helper is used by the destructor and assignment operator.
 */
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

/**
 * Copies another graph into this graph using deep copy.
 * Every EdgeNode is recreated so the two graphs do not share memory.
 */
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

/**
 * Adds one directed adjacency-list entry from src to dest.
 *
 * The public graph is undirected, but internally each undirected edge is stored
 * as two directed entries: src -> dest and dest -> src.
 * If the entry already exists, only its weight is updated.
 */
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

/**
 * Removes one directed adjacency-list entry from src to dest.
 * Returns true if an entry was removed and false otherwise.
 */
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

/**
 * Adds an undirected weighted edge to the graph.
 * The edge is stored in both directions inside the adjacency list.
 */
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

/**
 * Removes an undirected edge from the graph.
 * Since every edge is stored twice, both directed entries are removed.
 */
void Graph::removeEdge(int src, int dest) {
    validateVertex(src);
    validateVertex(dest);

    bool removedFromSrc = removeDirectedEdge(src, dest);
    bool removedFromDest = removeDirectedEdge(dest, src);

    if (!removedFromSrc || !removedFromDest) {
        throw std::runtime_error("Edge does not exist");
    }
}

/**
 * Prints the graph in a readable format.
 *
 * The actual implementation is still an adjacency list, but the function also
 * prints an adjacency matrix view because it is easier to read in the console.
 */
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

/**
 * Returns the fixed number of vertices in the graph.
 */
int Graph::getVertices() const {
    return vertices;
}

/**
 * Returns the adjacency list of a given vertex.
 */
const EdgeNode* Graph::getNeighbors(int vertex) const {
    validateVertex(vertex);
    return adjacencyList[vertex];
}

/**
 * Checks whether an edge exists between two vertices.
 */
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

/**
 * Returns the weight of an existing edge.
 */
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

/**
 * Counts the number of undirected edges in the graph.
 * Since each edge is stored twice, the directed count is divided by two.
 */
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

/**
 * Returns the total weight of all undirected edges.
 * Each edge is counted once by using only entries where src < dest.
 */
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
