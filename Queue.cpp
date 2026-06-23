// Email: yedidea9@gmail.com
#include "Queue.hpp"
#include <stdexcept>

namespace graph {

Queue::Queue(int capacity)
    : data(0), capacity(capacity), frontIndex(0), rearIndex(-1), currentSize(0) {
    if (capacity <= 0) {
        throw std::invalid_argument("Queue capacity must be positive");
    }
    data = new int[capacity];
}

Queue::Queue(const Queue& other)
    : data(0), capacity(other.capacity), frontIndex(other.frontIndex),
      rearIndex(other.rearIndex), currentSize(other.currentSize) {
    data = new int[capacity];
    for (int i = 0; i < capacity; i++) {
        data[i] = other.data[i];
    }
}

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

Queue::~Queue() {
    delete[] data;
}

void Queue::enqueue(int value) {
    if (isFull()) {
        throw std::runtime_error("Queue is full");
    }

    rearIndex = (rearIndex + 1) % capacity;
    data[rearIndex] = value;
    currentSize++;
}

int Queue::dequeue() {
    if (isEmpty()) {
        throw std::runtime_error("Queue is empty");
    }

    int value = data[frontIndex];
    frontIndex = (frontIndex + 1) % capacity;
    currentSize--;
    return value;
}

bool Queue::isEmpty() const {
    return currentSize == 0;
}

bool Queue::isFull() const {
    return currentSize == capacity;
}

}
