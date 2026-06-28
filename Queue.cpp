// Email: yedidea9@gmail.com
#include "Queue.hpp"
#include <stdexcept>

namespace graph {

/**
 * Creates a queue with a fixed capacity.
 */
Queue::Queue(int capacity)
    : data(0), capacity(capacity), frontIndex(0), rearIndex(-1), currentSize(0) {
    if (capacity <= 0) {
        throw std::invalid_argument("Queue capacity must be positive");
    }
    data = new int[capacity];
}

/**
 * Copy constructor.
 * Copies the internal array and queue indexes.
 */
Queue::Queue(const Queue& other)
    : data(0), capacity(other.capacity), frontIndex(other.frontIndex),
      rearIndex(other.rearIndex), currentSize(other.currentSize) {
    data = new int[capacity];
    for (int i = 0; i < capacity; i++) {
        data[i] = other.data[i];
    }
}

/**
 * Assignment operator.
 * Replaces the current queue data with a copy of another queue.
 */
Queue& Queue::operator=(const Queue& other) {
    if (this != &other) {
        delete[] data;
        capacity = other.capacity;
        frontIndex = other.frontIndex;
        rearIndex = other.rearIndex;
        currentSize = other.currentSize;
        data = new int[capacity];
        for (int i = 0; i < capacity; i++) {
            data[i] = other.data[i];
        }
    }
    return *this;
}

/**
 * Releases the dynamic array used by the queue.
 */
Queue::~Queue() {
    delete[] data;
}

/**
 * Adds a value to the back of the queue.
 * The indexes wrap around using modulo, so the array is used as a circular queue.
 */
void Queue::enqueue(int value) {
    if (isFull()) {
        throw std::runtime_error("Queue is full");
    }

    rearIndex = (rearIndex + 1) % capacity;
    data[rearIndex] = value;
    currentSize++;
}

/**
 * Removes and returns the value at the front of the queue.
 */
int Queue::dequeue() {
    if (isEmpty()) {
        throw std::runtime_error("Queue is empty");
    }

    int value = data[frontIndex];
    frontIndex = (frontIndex + 1) % capacity;
    currentSize--;
    return value;
}

/**
 * Returns true if the queue has no elements.
 */
bool Queue::isEmpty() const {
    return currentSize == 0;
}

/**
 * Returns true if the queue reached its fixed capacity.
 */
bool Queue::isFull() const {
    return currentSize == capacity;
}

}
