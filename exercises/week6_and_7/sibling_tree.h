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
		NodePtr child = Node::Create();     //create a new node
		child->setValue(value);             // set its value

		//add the first child if root has no children
        if (root_->child_ == nullptr){			
			this->root_->child_ = std::move(child);        //add it to the tree
		}
		else if (root_->child_->getSibling() == nullptr){
			//child has not sibling - so set one!
			root_->child_->setSibling(child);
		}
		else {
			//iterate through siblings until you find a sibling with no sibling, add the child there
			Node* current_node = this->root_->child_->getSibling();
			while(current_node->getSibling() != nullptr){
				current_node = current_node->getSibling();
			}
			current_node->setSibling(child);
		}
        
        
		return *this;
    }

    /**
     * Add a subtree to the top level of this tree, using move
     * semantics to "steal" the subtree's nodes.
     */
    Tree& addSubtree(Tree<T>&& sub_tree){

		//add the first child if root has no children
        if (this->root_->child_ == nullptr){			
			this->root_->child_ = std::move(sub_tree.root_);        //add it to the tree
		}
		else if (root_->child_->getSibling() == nullptr){
			//child has not sibling - so set one!
			root_->child_->setSibling(sub_tree.root_);
		}
		else {
			Node* current_node = this->root_->child_->getSibling();
			while(current_node->getSibling() != nullptr){
				current_node = current_node->getSibling();
			}
			current_node->setSibling(sub_tree.root_);
		}
        
        
		return *this;
	}

	/**
	 * Print out the tree to verify the structure
	 * TODO - update to print out any tree, currently only works for specific test code in sibling_tree_test.cpp
	*/
	void printTree(){
		std::cout << root_->getValue() << std::endl;
		std::cout << root_->child_->getValue() << std::endl;
		std::cout << root_->child_->getSibling()->getValue() << std::endl;
		std::cout << root_->child_->getSibling()->getSibling()->getValue() << std::endl;
		std::cout << root_->child_->getSibling()->getSibling()->child_->getValue() << std::endl;
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
		 * return a pointer to the node's sibling
		*/
		Node* getSibling(){
			return sibling_.get();
		}

		/**
		 * Set the sibling of the node
		*/
		void setSibling(NodePtr& sibling){
			sibling_ = std::move(sibling);
			return;
		}

		//! Compare this node to another by value
		bool operator < (const Node &other)
		{
			return value_ < other.value_;
		}

		/**
		 * Print a node's value and values of its child and sibling if instantiated
		 * TODO
		*/
		void printNode(){}

		NodePtr child_;
		NodePtr sibling_;
	private:
		T		value_;
		
	};

	NodePtr			root_;
};


