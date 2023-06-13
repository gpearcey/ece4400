#include <iostream>
#include <memory>
#include <cassert>
using namespace std;

template <typename T>
class LinkedList
{
    public:

    LinkedList()
    {
        head_ = Node::CreateNode();

        NodePtr tail = Node::CreateNode(head_.get());
        tail_ = tail.get();
        head_->append(std::move(tail));

    }

    LinkedList& operator << (T value)
    {

        Node* end = tail_->prev_;
        assert(end->next() == tail_);

        NodePtr n = Node::CreateNode(end);
        n->setValue(std::move(value));

        end->append(std::move(n));

        return *this;
    }
    void PrintList()
    {
        assert(head_->next() != tail_);

        Node* PrintPtr = head_->next_.get();

        cout << "List: ";
        while(PrintPtr != tail_)
        {
        cout << PrintPtr->value_ << ' ';
        PrintPtr = PrintPtr->next_.get();
        }
        cout << endl;
    }

    private:
    class Node;
    typedef std::unique_ptr<Node> NodePtr;

    class Node
    {
        public:
        static NodePtr CreateNode(Node* previous = nullptr)
        {
            return std::make_unique<Node> (previous);
        }

        Node(Node* previous = nullptr)
         : next_(nullptr), prev_(previous)
         {
         }

         void setValue(T value)
         {
            value_ = std::move(value);
         }

        void append(NodePtr node)
        {
            assert(!(node->next_));


            node->next_ = getNext();
            node->prev_ = this;

            if (node->next_)
            {
                node->next_->prev_ = node.get();
            }

            next_ = std::move(node);
        }

        Node* next()
        {
            return next_.get();
        }

        Node* prev()
        {
            return prev_;
        }

        NodePtr getNext()
        {
            return std::move(next_);
        }

        T& operator* ()
        {
            return value_;
        }
        
        T value_;
        NodePtr next_;
        Node* prev_;
    };

    NodePtr head_;
    Node* tail_;
};

int main()
{
    LinkedList<int> IntList;
    IntList << 2 << 16 << 82 << 25 << 5;
    IntList.PrintList();

    LinkedList<double> DoubleList;
    DoubleList << 2.22 << 3.14 << 9.99 << 2.718;
    DoubleList.PrintList();

    LinkedList<string> NamesList;
    NamesList << "Bob" << "John" << "Ella" << "James";
    NamesList.PrintList();

    return 0;
}