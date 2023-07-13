/*
 * Copyright 2018 Jonathan Anderson
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/**
 * Implement the insert, Node::min and Node::max methods recursively.

Implement the BinarySearchTree::print method using a recursive Node::print method.
*/


#include <cassert>
#include <cstddef>      // for definition of size_t
#include <functional>   // std::function
#include <memory>       // std::unique_ptr
#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
using namespace std;
template<typename T, typename Comparator = std::less<T>>
class BinarySearchTree
{
public:

	struct Node; // forward declaration
	std::unique_ptr<Node> root_;
	enum class Traversal
	{
		PreOrder,
		InOrder,
		PostOrder,
	};
	//! Does this tree contain the given value?
	bool contains(const T &value)
	{
		return (not empty() and root_->contains(value));
	}

	size_t maxDepth() const
	{
		if (empty())
		{
			return 0;
		}

		return root_->maxDepth()-1;
	}

	//! Is this tree empty?
	bool empty() const
	{
		return (not root_);
	}

	//! Insert a new value into the appropriate place in the tree.
	void insert(T value)
	{
		if (this->empty()){
			std::unique_ptr<Node> new_node = std::make_unique<Node>(std::move(value));
			this->root_ = std::move(new_node);
		}

		else{
			insert(std::move(value), root_);
		}
		
		
	}

	/**
	 * Output this tree in a GraphViz DOT representation as a
	 * directed graph ("digraph").
	 *
	 * Calls to this method will cause an entire graph (starting
	 * with "digraph G {") to be output to the given std::ostream.
	 *
	 * @param   o    the output stream to write to
	 */
	void printDot(std::ostream &o) const
	{
		o << "digraph {\n";

		if (root_){
			root_->printDot(o);
		}
		o << "}\n";

	}

	/**
	 * Find the minimum value in the tree.
	 *
	 * @pre   tree is not empty
	 */
	const T& min() const
	{
		assert(root_);
		return root_->min(this->compare_).value();
	}

	/**
	 * Find the minimum value in the tree.
	 *
	 * @pre   tree is not empty
	 */
	const T& max() const
	{
		assert(root_);
		return root_->max(this->compare_).value();
	}

	/**
	 * Remove a value (if it exists) from the tree.
	 *
	 * @returns   whether or not anything was found to remove
	 */
	bool remove(const T &&value)
	{
		return remove(value, root_);
	}

	/**
	 * Prints the tree structure. 
	 * 
	 * Prints the root first, then it's children on the next line, then the children of it's children on the following line, and so on.
	 * Iterates through the tree and places children in appropriate sub arrays based on node height, then prints each sub array. 
	*/
	void print(){
		int depth = this->maxDepth();

		std::vector<std::vector<T>> values_to_print;

		values_to_print.resize(depth + 1); //add one to include root

		this->root_->print(values_to_print, depth);

		for (int i = values_to_print.size() - 1; i >= 0; --i){
			for (const T& value : values_to_print[i]){
				cout << value << "  ";
			}
			cout << endl;
		}
	}

	/**
	 * An iterator that can traverse the BST in some order.
	 *
	 * The iterator contains a "current" node, a stack of parent nodes and
	 * a Traversal value to remind it which strategy it's following.
	 */
	class Iterator
	{
	public:
		/**
		 * Move to the next node in the tree that should be accessed.
		 *
		 * This operator method just calls private methods to try and
		 * keep the logic of the various traversal mechanisms clear.
		 */
		Iterator operator++(int)
		{
			if (this->order_ == Traversal::PreOrder)
			{
				this->PreOrder();
			}
			else if (this->order_ == Traversal::InOrder)
			{
				this->InOrder();
			}
			else if (this->order_ == Traversal::PostOrder)
			{
				this->PostOrder();
			}
			return *this;
		}

		//! Dereference the iterator at its current position
		const T &operator*()
		{
			return this->current_node_->element_;
		}

		//! Is this iterator *not* the same as another?
		bool operator!=(const Iterator &other)
		{
			if (this->current_node_ != other.current_node_)
			{
				return true; //node is not the same
			}
			return false; //node is the same
		}

		// add whatever else you need here
		std::stack<Node *> nodes_;
		Node *node_pointer_;
		Node *current_node_;
		Node *previous_node_;
		Traversal order_;

	private:
		/**
		 * PreOrder Traversal of tree
		*/
		void PreOrder()
		{
			bool node_incremented = false;

			while (!node_incremented)
			{
				if (nodes_.empty() == true && node_pointer_ == nullptr)
				{	// finished iterating through the tree
					current_node_ = nullptr; // set to null so it matches the end() iterator
					return;
				}

				if (node_pointer_ != nullptr)
				{
					// increment the current_node
					node_incremented = true; // lets us exit while loop
					current_node_ = node_pointer_;
					nodes_.push(node_pointer_); //add the node to the stack
					node_pointer_ = node_pointer_->left_.get(); // move to this node's left child
				}
				else
				{
					previous_node_ = nodes_.top(); // previous node is on top of the stack
					nodes_.pop(); //remove the previous node
					node_pointer_ = previous_node_->right_.get(); // move to the previous node's right child
				}
			}
			return;
		}

		/**
		 * In Order Tree Traversal
		*/
		void InOrder()
		{
			bool node_incremented = false;
			while (!node_incremented)
			{
				if (nodes_.empty() == true && node_pointer_ == nullptr)
				{
					// finished iterating through the tree
					current_node_ = nullptr; // set to null so it matches the end() iterator
					return;
				}

				if (node_pointer_ != nullptr)
				{
					// move to the left child
					nodes_.push(node_pointer_);
					node_pointer_ = node_pointer_->left_.get();
				}
				else
				{
					previous_node_ = nodes_.top();
					current_node_ = nodes_.top(); // set the current node for iterator to point to
					node_incremented = true; // lets us exit while loop 
					nodes_.pop();
					node_pointer_ = previous_node_->right_.get(); //move to the right child for next time
				}
			}
			return;
		}

		void PostOrder()
		{
			bool node_incremented = false;
			while (!node_incremented)
			{
				if (nodes_.empty() == true && node_pointer_ == nullptr)
				{ // finished iterating through the tree
					current_node_ = nullptr; // set to null so it matches the end() iterator
					return;
				}

				if (node_pointer_ != nullptr)
				{
					// move to the left child
					nodes_.push(node_pointer_);
					node_pointer_ = node_pointer_->left_.get();
				}
				else
				{
					current_node_ = nodes_.top();
					if (current_node_->right_ != nullptr and current_node_->right_.get() != previous_node_)
					{	
						// current node has a right child we haven't seen yet
						node_pointer_ = current_node_->right_.get();
					}
					else
					{
						// we have found the next node
						node_incremented = true; // lets us exit while loop
						previous_node_ = current_node_;
						nodes_.pop();

					}
				}
			}
			return;
		}
	};

	/**
	 * Returns an iterator that can be used to traverse the tree in the given order.
	 *
	 * This iterator should visit every node in the tree exactly once, after which
	 * it should test equal to the iterator returned from `end()`.
	 */
	Iterator begin(Traversal order)
	{
		Iterator iter;
		iter.order_ = order;
		if (order == Traversal::PreOrder)
		{
			iter.node_pointer_ = this->root_.get();
			iter.current_node_ = this->root_.get();
		}
		else if (order == Traversal::InOrder)
		{
			iter.node_pointer_ = this->root_.get();
		}
		else if (order == Traversal::PostOrder)
		{
			iter.node_pointer_ = this->root_.get();
		}
		iter++;
		return iter;
	}
	/**
	 * The end of a tree traversal.
	 *
	 * The iterator returned by this method should be usable as the end-of-iteration
	 * marker for any iterator on this tree, whether it was traversing the tree in
	 * pre-, in- or post-order.
	 */
	Iterator end()
	{
		Iterator iter;
		iter.current_node_ = nullptr;
		return iter;
	}



	struct Node
	{
		// Did you know that structs can have methods too?
		Node(T &&value)
			: element_(value), count_(1), left_(nullptr), right_(nullptr)
		{
		}

		/**
		 * Output information about this node in GraphViz DOT format.
		 *
		 * This will output information about this node
		 * (with no graph-level decorations such as "digraph G {")
		 * and recursively descend to its children.
		 */
		void printDot(std::ostream &o) const
		{
				o   << "  \"" << this << "\""
				<< " [ label = \"" << element_ << "\" ];\n";

			if (left_)
			{
				o << "  \"" << this << "\""
					<< " -> "
					<< "\"" << left_.get() << "\""
					<< " [ label = \"L\" ]\n";

				left_->printDot(o);
			}

			if (right_)
			{
				o << "  \"" << this << "\""
					<< " -> "
					<< "\"" << right_.get() << "\""
					<< " [ label = \"R\" ]\n";

				right_->printDot(o);
			}
		}

		const T& value() const { return element_; }

		bool contains(const T& value) const {
			if (this == nullptr){
				return false;
			}
			if (this->value() == value){
				return true;
			}
			return (this->left_->contains(value) || this->right_->contains(value));

		}
		Node& min(const Comparator& compare){
            Node* current_min = this;
            current_min = find_min(this, current_min, compare);
            return *current_min;            
        };

        Node* find_min(Node* node, Node* current_min, const Comparator& compare){
			if (node == nullptr){
				return current_min;
			}

			if (compare(node->value(),  current_min->value())) {
        		current_min = node;
    		}
    		Node* left_min = find_min(node->left_.get(), current_min, compare);
    		Node* right_min = find_min(node->right_.get(), current_min, compare);

    		if (left_min != nullptr &&  compare(left_min->value(), current_min->value())) {
				current_min = left_min;
    		}

    		if (right_min != nullptr &&  compare(right_min->value(), current_min->value())) {
				current_min = right_min;
    		}

    		return current_min;
        }

		Node& max(const Comparator& compare){
            Node* current_max = this;
            current_max = find_max(this, current_max, compare);
            return *current_max;      
		}

		Node* find_max(Node* node, Node* current_max, const Comparator& compare){
			if (node == nullptr){
				return current_max;
			}
   
   			if (compare(current_max->value(), node->value() )) {
        		current_max = node;
    		}
    		Node* left_max = find_max(node->left_.get(), current_max, compare);
    		Node* right_max = find_max(node->right_.get(), current_max, compare);

    		if (left_max != nullptr &&  compare(current_max->value(), left_max->value()) ) {
				current_max = left_max;
    		}

    		if ( right_max != nullptr && compare(current_max->value(),right_max->value() )) {
				current_max = right_max;
    		}

    		return current_max;
        }

		int print(std::vector<std::vector<T>>& values_vec, int prev_height){
			if (this ==  nullptr){
				return prev_height;
			}

			values_vec[prev_height].push_back(this->value());

    		if (this->left_ != nullptr){
				this->left_->print(values_vec, prev_height-1);
			}   		    

    		if (this->right_ != nullptr){
				this->right_->print(values_vec, prev_height-1);
			}    		    
			return prev_height;
		}

		T takeMin();
		size_t maxDepth() const{
			if (this == nullptr){
				return 0;
			}
			if (this->left_->maxDepth() > this->right_->maxDepth()){
				return this->left_->maxDepth() + 1;
			}

			return this->right_->maxDepth() + 1;
			
		}

		/**
		 * returns the height of a node
		 * 
		 * @returns int
		 * 
		 */
		size_t getHeight(std::unique_ptr<Node> &node){
			if (node == nullptr) {
				return 0;
			}
			size_t left_height = getHeight(node->left_);
			size_t right_height = getHeight(node->right_);
			return std::max(left_height, right_height) + 1;
		}

		/**
		 * Updates the height of a node and the heights of it's children
		 * 
		 * @returns int
		 * 
		 */
		void updateHeights(){
			if (this == nullptr) {
				return;
			}

			int left_height = 0;
			int right_height = 0;
			if (this->left_ != nullptr){
				left_height = getHeight(this->left_);
			}
			if (this->right_ != nullptr){
				right_height = getHeight(this->left_);
			}
			if (left_height > right_height){
				this->height_ = left_height +1;
			}
			else {
				this->height_ = right_height +1;
			}
			return;
		}

		T element_;
		size_t count_;
		int height_;
		std::unique_ptr<Node> left_;
		std::unique_ptr<Node> right_;
		int bf_;
	};
private:
	/**
	 * Internal implementation of recursive insert.
	 *
	 * @param   value      the value to insert
	 * @param   node       the root of the (sub-)tree being inserted into;
	 *                     may be null if the (sub-)tree is empty
	 */
	int insert(T &&value, std::unique_ptr<Node> &node){
		if (compare_(value, node->value())){ 
			if (node->left_ == nullptr){
				std::unique_ptr<Node> new_node = std::make_unique<Node>(std::move(value));
				new_node_->bf_ = 0;
				node->left_ = std::move(new_node);
				return 0;
			}
			else{
				insert(std::move(value), node->left_);
			}			
		}
		else if (compare_(node->value(), value)){
			if (node->right_ == nullptr){
				std::unique_ptr<Node> new_node = std::make_unique<Node>(std::move(value));
				node->right_ = std::move(new_node);
				return 0;
			}
			else{
				insert(std::move(value), node->right_);
			}
			
		}
		else {
			node->count_++;
		}

		node->bf_ = abs(left) - abs(right)
		//this->root_->updateHeights();

		return;
	}




	/**
	 * Internal implementation of recursive removal.
	 *
	 * @param   value      the value to remove
	 * @param   node       the root of the (sub-)tree being inserted into;
	 *                     may be null if the (sub-)tree is empty
	 */
	bool remove(const T &value, std::unique_ptr<Node> &node){
		if (not node){
			return false; //tree does not contain value
		}
		else if(compare_(value, node->element_)){
			return remove(value, node->left_); //traverse left side
		}
		else if(compare_(node->element_, value)){
			return remove(value, node->right_); //traverse right side
		}
		else if (node->count_ > 1){ //multiple nodes with same value, just decrement the count. 
			node->count_--;
			return true;
		}
		else if (node->left_ and node->right_){
			//node has two children
			T minOfMax = node->right_->min(compare_).element_;
			remove(minOfMax, node->right_);
			node->element_ = std::move(minOfMax);
		}
		else{
			node.swap(node->left_ ? node->left_ : node->right_); //node has zero or one children
		}
		return true;
	}

    Comparator compare_;

};