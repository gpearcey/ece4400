#include <iostream>
#include <memory>
#include <list>

template <typename T>
class Queue
{
private:
    std::list<T> values_;

public:
    void enqueue(
        values.emplace_back(););
    void dequeue(
        values.pop_front(););
    );
    void empty(
        values.empty(););
    );
};

int main()
{
    Queue<int> queue;
    queue.enqueue(1);

    return 0;
}