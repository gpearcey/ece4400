#include <iostream>
#include <memory>
#include <cassert>
#include <vector>

template <typename T>
std::ostream &operator<<(std::ostream &o, const std::vector<T> &v)
{
    o << "[";
    for (const auto &x : v)
    {
        o << " " << x;
    }
    o << " ]";

    return o;
}

template <typename T>
class LinkedList
{
public:
    //! Construct an empty linked list.
    LinkedList()
    {
        // Create sentinel nodes for the beginning and end of the list.
        head_ = Node::Create();

        NodePtr tail = Node::Create(head_.get());
        tail_ = tail.get();
        head_->append(std::move(tail));
    }

    /**
     * Append a new value to the end of the list.
     */
    LinkedList &operator<<(T rhs)
    {
        // Find the last node that isn't the end sentinel
        Node *last = tail_->prev();
        assert(last->next() == tail_);

        // Create the new node to be inserted before the end
        NodePtr n = Node::Create(last);
        n->setValue(std::move(rhs));

        // Append the new node after the previously-last node
        last->append(std::move(n));

        return *this;
    }

    T &front()
    {
        assert(head_->next() != tail_ && "called front() on empty list");
        return **head_->next();
    }

    /**
     * Retrieve a reference to the last element in the list.
     *
     * @pre    the list should not be empty
     */
    T &back()
    {
        assert(head_->next() != tail_ && "called back() on empty list");
        return **tail_->prev();
    }

private:
    //
    // NodePtr will be more convenient to use than std::unique_ptr<Node>.
    // We can create this new type name with typedef or using, but first we
    // need to forward-declare the Node type.
    //
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

        /**
         * Append a node as the "next" node from this one.
         */
        void append(NodePtr n)
        {
            // The new node should not have an existing "next" pointer
            assert(not n->next_);

            // Set up the new node's relationships with us and our old "next"
            // node (which the new one is being inserted before)
            n->next_ = takeNext();
            n->prev_ = this;

            if (n->next_)
            {
                n->next_->prev_ = n.get();
            }

            // Update our own "next" pointer
            next_ = std::move(n);
        }

        Node *next()
        {
            return next_.get();
        }

        Node *prev()
        {
            return prev_;
        }

        /**
         * Steal this node's "next" node.
         */
        NodePtr takeNext()
        {
            return std::move(next_);
        }

        /**
         * Dereference operator: get this node's value.
         *
         * @pre    node is not a sentinel
         */
        T &operator*()
        {
            return value_;
        }

        //! Compare this node to another by value
        bool operator<(const Node &other)
        {
            return value_ < other.value_;
        }

    private:
        T value_;
        NodePtr next_;
        Node *prev_;
    };

    NodePtr head_;
    Node *tail_;
};

int main()
{

    // works for ints, doubles and strings
    LinkedList<std::string> list;

    list << "1"
         << "2"
         << "3";

    std::cout << "front: " << list.front() << std::endl;
    std::cout << "back: " << list.back() << std::endl;

    return 0;
}
