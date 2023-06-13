/**
 * Implement a tree ADT (abstract data type) in which each node can have an arbitrary number of children.
 *  Implement the following methods to populate your tree. Write test code to build a tree with some pre-defined structure and 
 * use a debugger to verify that the tree has the structure you intended.
*/



#include <list>
#include <iostream>
#include <memory>
using namespace std;


template<typename T>
class Tree
{
public:
	//! Construct an empty linked list.
	Tree()
	{
		// Create sentinel nodes for the beginning and end of the list.
		root_ = Node::Create();
	}
    /**
     * Set the value of the tree's root node.
     */
    Tree& setRoot(T value){
        root_.setValue(value);
    }

    /**
     * Add a leaf node to the top level of this tree.
     */
    Tree& addChild(T value){
        NodePtr child = Node::Create();
        child.setValue(value);
        root_.append(std::move(child));
    }

    /**
     * Add a subtree to the top level of this tree, using move
     * semantics to "steal" the subtree's nodes.
     */
    Tree& addSubtree(Tree<T>&&);

	/**
	 * Append a new value to the end of the list.
	 */
	LinkedList& operator << (T rhs)
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

	/**
	 * Retrieve a reference to the first element in the list.
	 *
	 * @pre    the list should not be empty
	 */
	T& front()
	{
		assert(head_->next() != tail_ && "called front() on empty list");
		return **head_->next();
	}

	/**
	 * Retrieve a reference to the last element in the list.
	 *
	 * @pre    the list should not be empty
	 */
	T& back()
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
			: next_(nullptr)
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

			if (n->next_) {
				n->next_->prev_ = n.get();
			}

			// Update our own "next" pointer
			next_ = std::move(n);
		}

		Node* next()
		{
			return next_.get();
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
		T& operator* ()
		{
			return value_;
		}

		//! Compare this node to another by value
		bool operator < (const Node &other)
		{
			return value_ < other.value_;
		}

	private:
		T		value_;

		std::list<NodePtr> children_;
	};

	NodePtr			root_;
};


int main()
{
	LinkedList<double> numbers;
	numbers << 3.1415 << 2 << 42;

	cout << "front of numbers: " << numbers.front() << endl;
	cout << "back of numbers: " << numbers.back() << endl;

	LinkedList<unique_ptr<double>> pointers;
	pointers << make_unique<double>(3.14);

	return 0;
}