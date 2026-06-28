// Email: yedidea9@gmail.com
#include "PriorityQueue.hpp"
#include <stdexcept>

namespace graph {

/**
 * Creates a priority queue with a fixed capacity.
 */
PriorityQueue::PriorityQueue(int capacity) : data(0), capacity(capacity), currentSize(0) {
    if (capacity <= 0) {
        throw std::invalid_argument("PriorityQueue capacity must be positive");
    }
    data = new PQItem[capacity];
}

/**
 * Copy constructor.
 * Copies all currently stored priority queue items.
 */
PriorityQueue::PriorityQueue(const PriorityQueue& other)
    : data(0), capacity(other.capacity), currentSize(other.currentSize) {
    data = new PQItem[capacity];
    for (int i = 0; i < currentSize; i++) {
        data[i] = other.data[i];
    }
}

/**
 * Assignment operator.
 * Replaces the current queue data with a copy of another priority queue.
 */
PriorityQueue& PriorityQueue::operator=(const PriorityQueue& other) {
    if (this != &other) {
        delete[] data;
        capacity = other.capacity;
        currentSize = other.currentSize;
        data = new PQItem[capacity];
        for (int i = 0; i < currentSize; i++) {
            data[i] = other.data[i];
        }
    }
    return *this;
}

/**
 * Releases the dynamic array used by the priority queue.
 */
PriorityQueue::~PriorityQueue() {
    delete[] data;
}

/**
 * Inserts a new vertex with a given priority.
 */
void PriorityQueue::push(int vertex, int priority) {
    if (currentSize == capacity) {
        throw std::runtime_error("PriorityQueue is full");
    }

    data[currentSize].vertex = vertex;
    data[currentSize].priority = priority;
    currentSize++;
}

/**
 * Decreases the priority of an existing vertex.
 * If the new priority is not smaller, the item is left unchanged.
 */
void PriorityQueue::decreaseKey(int vertex, int newPriority) {
    for (int i = 0; i < currentSize; i++) {
        if (data[i].vertex == vertex) {
            if (newPriority < data[i].priority) {
                data[i].priority = newPriority;
            }
            return;
        }
    }

    throw std::runtime_error("Vertex was not found in PriorityQueue");
}

/**
 * Checks whether a vertex currently exists in the queue.
 */
bool PriorityQueue::contains(int vertex) const {
    for (int i = 0; i < currentSize; i++) {
        if (data[i].vertex == vertex) {
            return true;
        }
    }

    return false;
}

/**
 * Removes and returns the item with the smallest priority.
 * The implementation scans the array linearly to find the minimum.
 */
PQItem PriorityQueue::popMin() {
    if (isEmpty()) {
        throw std::runtime_error("PriorityQueue is empty");
    }

    int minIndex = 0;
    for (int i = 1; i < currentSize; i++) {
        if (data[i].priority < data[minIndex].priority) {
            minIndex = i;
        }
    }

    PQItem result = data[minIndex];
    data[minIndex] = data[currentSize - 1];
    currentSize--;
    return result;
}

/**
 * Returns true if the priority queue has no items.
 */
bool PriorityQueue::isEmpty() const {
    return currentSize == 0;
}

}
