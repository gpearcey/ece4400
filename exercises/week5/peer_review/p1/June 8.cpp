#include <iostream>
#include <list>
using namespace std;

template<typename T>
class queue
{
public:
    queue()
    : thisQueue()
    {};
    
    //enqueue adds the input value to the end of the list
    void enqueue(T value)
    {
        thisQueue.push_back(value);
    }
    
    //dequeue returns the first value in the queue and then removes it
    T dequeue()
    {
        T value = *thisQueue.begin();
        thisQueue.pop_front();
        return value;
    }
    
    bool empty()
    {
        return thisQueue.empty();
    };
    
private:
    list<T> thisQueue;
    
};

int main()
{
    string operation;
    int value;
    queue<int> theQueue;
    
    //While loop to loop the code for as many operations as we want to complete
    while(true)
    {
        cout << "Enter Operation: ";
        cin >> operation;
        
        //Change operation input to upper-case letters for simplier if statements later
        for (int i = 0; i < operation.length(); i++)
        {
            operation[i] = toupper(operation[i]);
        }
        
        //Check if the operation requires us to cin a value
        if (operation == "ENQUEUE")
        {
            cin >> value;
        }
        
        //If statements to conduct whatever operation we need
        if (operation == "ENQUEUE")
        {
           theQueue.enqueue(value);
        }
        else if (operation == "DEQUEUE")
        {
            if (theQueue.empty())
            {
                cout << "The queue is empty!" << endl;
            }
            else
            {
                cout << "The dequeued value is: " << theQueue.dequeue() << endl;
            }
        }
        //Added option to enter quit/exit to end the loop
        else if (operation == "QUIT" or operation == "EXIT")
        {
            exit(EXIT_SUCCESS);
        }
        else{
            cout << "Invalid operation!";
        }
    }
    return 0;
}
