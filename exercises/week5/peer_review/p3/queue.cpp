#include <iostream>
#include <list>
using namespace std;

template <typename T>
class Queue
{
    public:

    //creates empty queue object
    Queue()
    {
    }

    //appends specified element to back of queue
    void enqueue(T q)
    {
        queue.push_back(q);
    }
    
    //removes specified element from queue 
    //assumes every element only occurs once
    void dequeue(T q)
    {
        if (empty() == true)
            cout << "ERROR: Queue is Empty" << endl;
        else
        {
            queue.remove(q);
        }
    }
    
    //returns bool value determaining if queue is empty
    bool empty()
    {
        return queue.empty(); 
    }

    //extra method added for an easy access queue output
    void printQueue()
    {
        cout << "Queue: ";
        for (T element : queue)
        {
            cout << element << " ";
        }
        cout <<  endl;
    }

    ~Queue()
    {
    }

    private:
    std::list<T> queue;
};

int main()
{
    //implemented Queue system
    Queue<int> intQueue;
    char operation = '0'; //initiallized with a dummy character
    int value;

    
    while(operation != 'Q' or operation != 'q') //q operation exits the menu loop
    {
        cout << "Please Enter a Valid Operation Symbol:" << endl;
        cout << "[A]    Add to Queue" << endl;
        cout << "[R]    Remove from Queue" << endl;
        cout << "[V]    View Queue" << endl;
        cout << "[Q]    Quit Menu" << endl;

        cin >> operation;

        switch(operation)
        {
            case 'A': 
            case 'a':
            cout << "Enter value to enqueue: ";
            cin >> value;
            intQueue.enqueue(value);

            break;
            
            case 'R':
            case 'r':
            cout << "Enter value to dequeue: ";
            cin >> value;
            intQueue.dequeue(value);
            break;

            case 'V':
            case 'v':
            intQueue.printQueue();
            break;

            case 'Q':
            case 'q':
            break;

            default:
            cout << "ERROR: Invalid Operation" << endl;
            break;
        }

    }
    return 0;
}