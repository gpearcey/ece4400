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
        this->root_->setValue(value);
		return *this;

    }

    /**
     * Add a leaf node to the top level of this tree.
     */
    Tree& addChild(T value){
        NodePtr child = Node::Create();    //create a new node
        child->setValue(value);            // set its value
        this->root_->append(child);        //add it to the tree
		return *this;
    }

    /**
     * Add a subtree to the top level of this tree, using move
     * semantics to "steal" the subtree's nodes.
     */
    Tree& addSubtree(Tree<T>&& sub_tree){
		this->root_->append(sub_tree.root_);
		return *this;
	}

	/**
	 * Print out the tree to verify the structure
	*/
	void printTree(){
		std::cout << "Root has value " << this->root_->getValue()<< std::endl;  // print root value
		if (this->root_->isEmpty()){
			std::cout << "root has no children" << std::endl;
			return;
		}

		//print all children of the root
		for (auto iter = this->root_->children_.begin(); iter != this->root_->children_.end(); ++iter){			
    		(*iter)->printNode();	
			std::cout << "" << std::endl;
		}
		return;
	}


private:
	//! Node class to represent tree nodes
	class Node; // forward declaration
	using NodePtr = std::unique_ptr<Node>;

	class Node
	{
	public:
		static NodePtr Create()
		{
			return std::make_unique<Node>();
		}

		//! Default constructor
		Node(){}

		/** 
		 * Set the node's value
		*/
		void setValue(T value)
		{
			value_ = std::move(value);
		}

		/** 
		 * Get the node's value
		*/
		T getValue(){
			return value_;
		}

		/**
		 * Append a new node
		 */
		void append(NodePtr& n)
		{
			// Add new node to this node's children
			this->children_.push_back(std::move(n));
		}

		/**
		 * Dereference operator: get this node's value.
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

		/**
		 * Check if node is empty
		*/
		bool isEmpty(){
			return children_.empty();
		}

		/**
		 * Print a child and it's children to the terminal
		*/
		void printNode(){		
			//Check if node has no children and return if so
			if (this->children_.empty()){
				std::cout << this->value_ << std::endl;
				return;
			}
			//iterate through all of the child's children recursively
			for (auto iter = this->children_.begin(); iter != this->children_.end(); ++iter){
    			std::cout << "node with value " << value_ << " has children with values: " << std::endl;
				(*iter)->printNode();			
			}
			return;
		}
		std::list<NodePtr> children_;
	private:
		T		value_;

		
	};

	NodePtr			root_;
};


