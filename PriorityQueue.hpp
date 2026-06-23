// Email: yedidea9@gmail.com
#ifndef PRIORITY_QUEUE_HPP
#define PRIORITY_QUEUE_HPP

namespace graph {

struct PQItem {
    int vertex;
    int priority;
};

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
