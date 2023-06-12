#include <iostream>
#include <memory>
using namespace std;

template <typename T>
class linkedList
{
public:
    //Constructor creates sentinal node for the front and end of the list
    linkedList()
    {
        head_ = Node::Create();
        NodePtr tail = Node::Create(head_.get());
        tail_ = tail.get();
        head_->append(std::move(tail));
    }
    
    T& front()
    {
        return **head_->next();
    }
    T& back()
    {
        return **tail_->prev();
    }
    
    //Operator overload to add a new node to the end of the list
    linkedList& operator<< (T value)
    {
        Node *last = tail_->prev();
        assert(last->next() == tail_);

        //Create ptr to the new node (to come after the old last node) and then assign it value and append it to the list
        NodePtr newNode = Node::Create(last);
        newNode->setValue(std::move(value));
        last->append(std::move(newNode));
        return *this;
    };
    
private:
    class Node;
    using NodePtr = std::unique_ptr<Node>;
    
    class Node
    {
    public:
        static NodePtr Create(Node *predecessor = nullptr)
        {
            return std::make_unique<Node>(predecessor);
        }

        Node(Node *predecessor = nullptr)
            : next_(nullptr), prev_(predecessor)
        {
        }

        void setValue(T value)
        {
            value_ = std::move(value);
        }

        //Function to add a node to the end of the list
        void append(NodePtr n)
        {
            assert(not n->next_);
            
            //Changing existing ptrs to account for the new node
            n->next_ = takeNext();
            n->prev_ = this;
            //Changing the next node afer the one we added to point back to the new node
            if (n->next_)
            {
                n->next_->prev_ = n.get();
            }
            next_ = std::move(n);
        }

        Node* next()
        {
            return next_.get();
        }
        Node* prev()
        {
            return prev_;
        }

        //Returns pointer to the next node in the list
        NodePtr takeNext()
        {
            return std::move(next_);
        }
        
        T& operator* ()
        {
            return value_;
        }

        bool operator < (const Node &other)
        {
            return value_ < other.value_;
        }
    private:
        T value_;
        NodePtr next_;
        Node* prev_;
    };
    
    NodePtr head_;
    Node* tail_;
};

int main()
{
    linkedList<double> numbers;
    numbers << 321.123 << 294.21 << 67;

    cout << "front of the doubles list: " << numbers.front() << endl;
    cout << "back of the doubles list: " << numbers.back() << endl;

    linkedList<string> strings;
    strings << "Hey" << "Hello" << "Goodbye";

    cout << "front of the strings list: " << strings.front() << endl;
    cout << "back of the strings list: " << strings.back() << endl;
    return 0;
}
