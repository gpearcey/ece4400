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
	//! Construct an empty tree.
	Tree()
	{
		// Create the root node.
		root_ = std::make_unique<Node>();
	}
    /**
     * Set the value of the tree's root node.
     */
    Tree& setRoot(T value){
        root_.setValue(value);
		return *this;

    }

    /**
     * Add a leaf node to the top level of this tree.
     */
    Tree& addChild(T value){
        NodePtr child = Node::Create();
        child.setValue(value);
        root_.append(std::move(child));
		return *this;
    }

    /**
     * Add a subtree to the top level of this tree, using move
     * semantics to "steal" the subtree's nodes.
     */
    Tree& addSubtree(Tree<T>&& sub_tree){
		root_.append(std::move(sub_tree.root_));
		return *this;
	}

	void printTree(){
		if (this->root_.children_.empty()){
			std::cout << "root has no children" << std::endl;
			return;
		}
		for (auto child : this->root_.children_){
			child.printNode();
		}
		return;
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
		static NodePtr Create()
		{
			return std::make_unique<Node>();
		}

		Node(){}
		

		void setValue(T value)
		{
			value_ = std::move(value);
		}

		/**
		 * Append a new node
		 */
		void append(NodePtr n)
		{
			// Add new node to this node's children
			this->children_.push_back = std::move(n);
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

		void printNode(){
			std::cout << this->value_ << std::endl;
			if (this->children_.empty()){
				return;
			}
			for (auto child : this->children_){
				child.printNode();
			}
			return;
		}

	private:
		T		value_;

		std::list<NodePtr> children_;
	};

	NodePtr			root_;
};


