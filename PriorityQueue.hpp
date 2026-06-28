// Email: yedidea9@gmail.com
#ifndef PRIORITY_QUEUE_HPP
#define PRIORITY_QUEUE_HPP

namespace graph {

/**
 * Represents one item in the priority queue.
 * The item stores a vertex and its priority value.
 */
struct PQItem {
    int vertex;
    int priority;
};

/**
 * A simple minimum priority queue implemented with a dynamic array.
 *
 * The queue is used by Dijkstra and Prim. It supports decreaseKey, but the
 * implementation is intentionally simple and uses linear search.
 */
class PriorityQueue {
private:
    PQItem* data;
    int capacity;
    int currentSize;

public:
    PriorityQueue(int capacity);
    PriorityQueue(const PriorityQueue& other);
    PriorityQueue& operator=(const PriorityQueue& other);
    ~PriorityQueue();

    void push(int vertex, int priority);
    void decreaseKey(int vertex, int newPriority);
    bool contains(int vertex) const;
    PQItem popMin();
    bool isEmpty() const;
};

}

#endif
