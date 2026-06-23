// Email: yedidea9@gmail.com
#ifndef QUEUE_HPP
#define QUEUE_HPP

namespace graph {

class Queue {
private:
    int* data;
    int capacity;
    int frontIndex;
    int rearIndex;
    int currentSize;

public:
    Queue(int capacity);
    Queue(const Queue& other);
    Queue& operator=(const Queue& other);
    ~Queue();

    void enqueue(int value);
    int dequeue();
    bool isEmpty() const;
    bool isFull() const;
};

}

#endif
