#include <list>
//Implement a template queue class using a std::list field. Provide enqueue(), dequeue() and empty() methods (which tests whether the queue is currently empty) — no iterators required.


using namespace std;

template<typename T>
class Queue
{
public:
    Queue() : size_(0){};

    void enqueue(T item){
        queue_.push_back(item);
        size_++;
    };

    T dequeue(){
        T item = queue_.back();
        queue_.pop_back();
        size_--;
        return item;
    };

    bool empty(){
        if (size_ == 0){
            return true;
        }
        else{
            return false;
        }
    };

private:
    std::list<T> queue_;
    size_t size_;
};

