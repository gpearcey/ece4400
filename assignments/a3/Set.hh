/*
 * Copyright 2020, 2023 Jonathan Anderson
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

#ifndef SET_H_
#define SET_H_

#include <cassert>      // for assert()
#include <cstddef>      // for definition of size_t
#include <utility>      // for std::move()
#include <memory>       // std::unique_ptr
#include <stack>        // std::stack
//
// This preprocessor definition expands to a function
// body that contains an assertion that will provoke
// a run-time error. You can remove UNIMPLEMENTED from
// each method as you implement it, and remove the
// following line once you've implemented everything.
//
#define UNIMPLEMENTED \
{ \
	assert(false && "not implemented yet"); \
}

using namespace std;


template<typename M>
class Stack
{
public:
	class Node_s; //forward declaration

	//! An iterator over the list
	class iterator_s
	{
	public:
		/**
		 * The dereference operator.
		 *
		 * @returns   a reference to the "current" element
		 */
		M operator*(){
			return this->node_pointer_->getValue();
		};

		/**
		 * Pre-increment operator (i.e., `++i`).
		 *
		 * This method increments the iterator and then returns a
		 * reference to the newly-incremented iterator.
		 *
		 * @returns   a reference to this iterator, after incrementing
		 */
		iterator_s& operator++(){
			if (node_pointer_){
				this->node_pointer_ = this->node_pointer_->getNext();
			}			
			return *this;			
		};

		/**
		 * Post-increment operator (i.e., `i++`).
		 *
		 * This method returns a copy of this iterator as it currently
		 * is (i.e., pointing where it currently points) and _then_
		 * increments itself.
		 *
		 * @param     ignored   this is only used to distinguish the two
		 *                      increment operators (pre- and post-)
		 *                      from each other: its value should be
		 *                      ignored
		 *
		 * @returns   an iterator to the previously-current element
		 */
		iterator_s operator++(int ignored){
			iterator_s i = *this;
            ++*this;						
			return i;
		}

		//! Is this iterator pointing at the same place as another one?
		bool operator== (const iterator_s& other) const{
			if (this->node_pointer_ == other.node_pointer_){
				return true;
			}
			else{
				return false;
			}
		};

		//! Is this iterator pointing at a different place from another?
		bool operator!= (const iterator_s& other) const{
			if (this->node_pointer_ == other.node_pointer_){
				return false;
			}
			else{
				return true;
			}
		}

		Node_s* node_pointer_;		
	};


	//! Default constructor
	Stack(){
		head_ = std::make_unique<Node_s>();
	};

	//! Copy constructor
	Stack(const Stack& other){
		head_ = std::make_unique<Node_s>();
		this->head_ = std::make_unique<Node_s>(*other.head_);

	};

	//! Move constructor
	Stack(Stack&& other){
		head_ = std::make_unique<Node_s>();
		if (this != &other) {
			this->head_->next_ = std::move(other.head_->next_);
		}
	};

	//! Destructor
	~Stack(){};

	//! Copy assignment operator
	Stack& operator= (const Stack& other){
        this->head_ = std::make_unique<Node_s>(*other.head_);
		return *this;
	}

	//! Move assignment operator
	Stack& operator= (Stack&& other){
		if (this != &other) {
			this->head_->next_ = std::move(other.head_->next_);
		}
		return *this;
	};


	//
	// Accessors:
	//
	//! How many elements are in this list?
	size_t size() const{

		int count = 0;
		if (head_->getNext() == nullptr){
			count = 0;
		}else{
			//traverse through the list until the last node is reached
			Node_s* current_node = head_->getNext();
			while (current_node->getNext() != nullptr){
				current_node = current_node->getNext();
				count++;
			}
			count++;
		}
		return count;
	
	}

	//! Is this list empty?
	bool empty() const{
		if (head_->getNext() == nullptr){
			return true;
		}
		else{
			return false;
		}
	};

	//! Get an iterator to the beginning of the list
	iterator_s begin(){
		iterator_s i;
		i.node_pointer_ = this->head_->getNext();
		return i;

	};

	//! Get an iterator just past the end of the list
	iterator_s end(){
		iterator_s i;
		//set last node to point to the new node

		if (head_->getNext() == nullptr){
			i.node_pointer_ = head_.get();
		}else{
			//traverse through the list until the last node is reached
			Node_s* current_node = head_->getNext();
			while (current_node->getNext() != nullptr){
				current_node = current_node->getNext();
			}
			//set the last node to point to the new node
			i.node_pointer_ = current_node->getNext();
		}
		return i;
	}


	//
	// Mutators:
	//

	//! Copy an element to the front of the list
	void push(const M& value){

		//create new node
		std::unique_ptr<Node_s> new_node = std::make_unique<Node_s>(value);
		
		//set new node's next pointer to the node that used to be at the front if list is not empty
		if (head_->getNext() != nullptr){	
			new_node->setNext(this->head_->next_);
		}

		//set the head to point to the new node
		this->head_->setNext(new_node);
		cout << value << endl;
		return;
	};

	//! Move an element to the front of the list
	void push(M&& value){
		std::unique_ptr<Node_s> new_node = std::make_unique<Node_s>(std::move(value));		

		//set new node's next pointer to the node that used to be at the front if list is not empty
		if (head_->getNext() != nullptr){	
			new_node->setNext(this->head_->next_);
		}

		//set the head to point to the new node
		this->head_->setNext(new_node);
		return;
	};

	//! Copy an element to the back of the list
	M top(){

		M ret;

		if (this->empty()){
			std::cout << "Stack is empty" << std::endl;
			return nullptr;
		}

		if (head_->getNext() == nullptr){ 
			return nullptr;

		}else if(head_->getNext()->getNext() == nullptr) {
			ret = head_->getNext()->getValue();
		}
		else{
			//traverse through the list until the last node is reached
			Node_s* current_node = head_->getNext();
			while (current_node->getNext()->getNext() != nullptr){
				current_node = current_node->getNext();
			}
			//set the second last node's next node to to null to remove the last node
			M ret = current_node->getNext()->getValue();
		}

		return ret;
	};

	//! Copy an element to the back of the list
	void pop(){

		if (this->empty()){
			std::cout << "Stack is empty" << std::endl;
			return;
		}

		if (head_->getNext() == nullptr){ 
			return;

		}else if(head_->getNext()->getNext() == nullptr) {
			head_->getNext()->next_ = nullptr;
		}
		else{
			//traverse through the list until the last node is reached
			Node_s* current_node = head_->getNext();
			while (current_node->getNext()->getNext() != nullptr){
				current_node = current_node->getNext();
			}
			//set the second last node's next node to to null to remove the last node
			current_node->next_ = nullptr;
		}

		return;
	};




	//! Represents a list element - contains a value and a pointer to the next element
	class Node_s{
	public:
		//! Default constructor
		Node_s() : next_(nullptr){};

		//! Constructor to initialize with a value
		Node_s(M value) : value_(std::move(value)), next_(nullptr){};

		//! Copy constructor
		Node_s(const Node_s& other): value_(other.value_), next_(nullptr){
    		if (other.next_) {
    		    next_ = std::make_unique<Node_s>(*other.next_);
    		}
		};

		//! Move constructor
		Node_s(Node_s&& other) : value_(std::move(other.value_)), next_(nullptr){
    		if (other.next_) {
    		    next_ = std::move(other.next_);
    		}
		};

		//
		// Accessors:
		//
		M getValue(){
			return value_;
		};

		Node_s* getNext(){
			return next_.get();
		};

		//
		// Mutators:
		//		
		void setValue(M value){
			value_ = std::move(value);
			return;
		};
		
		void setNext(std::unique_ptr<Node_s>& next_node){
			next_ = std::move(next_node);
			return;
		};

		//! Destructor
		~Node_s(){};

		// Pointer to next element
		std::unique_ptr<Node_s> next_;

	private:
		// Value of element
		M value_;
		
	};
private:
	// Represents the head of the list
	std::unique_ptr<Node_s> head_;
};

/**
 * A set that holds values, ignoring duplicates.
 * 
 * Todo:
 * @todo get rid of std::stack
 * @todo copy constructor
 * @todo move constructor
 * @todo make sure pre increment is correct
 * @todo intersection
 * @todo union
 * @todo find
 * @todo const find
 * 
 * 
 */
template<typename T, typename Comparator = std::less<T>> //TODO remove std::less
class Set
{
public:
    struct Node; // forward declaration
	std::unique_ptr<Node> root_;
	//! Default constructor
	Set() {} 

	//! Copy constructor
	Set(const Set&) UNIMPLEMENTED

	// Move constructor
	Set(Set&&) UNIMPLEMENTED

	//! Add an element to this set.
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
	 * Remove a value (if it exists) from the tree.
	 *
	 * @returns   whether or not anything was found to remove
	 */
	bool remove(const T &&value)
	{
		return remove(value, root_);
	}

	//! Is this set the empty set?
	bool empty() const
    {
        return (not root_);
    }

	//! Is a specified element already in the set?
	bool contains(const T& value) const
    {
        return (not empty() and root_->contains(value));
    }

	//! Compute our intersection with another set.
	Set<T> intersection(const Set<T>& other) UNIMPLEMENTED

	//! Compute our union with another set.
	Set<T> setUnion(const Set<T>&) UNIMPLEMENTED

	//! An iterator over the set's values that promises not to change them.
	struct ConstIterator //TODO -> inorder traversal
	{
		const T& operator*() const
        {
            return this->current_node_->element_;
        }

		ConstIterator& operator++() //TODO - is this really pre inc?
        {
            this->InOrder();
            return *this;
        }

		//! Is this iterator *not* the same as another?
		bool operator!=(const ConstIterator &other)
		{
			if (this->current_node_ != other.current_node_)
			{
				return true; //node is not the same
			}
			return false; //node is the same
		}

        Stack<Node*> nodes_;
		Node *node_pointer_;
		Node *current_node_;
		Node *previous_node_;
    private:

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
					nodes_.push(&node_pointer_);
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
	};

	//! An iterator over the set's values that *is* allowed to change values.
	struct Iterator //TODO -> inorder traversal
	{
		T& operator*() const
        {
            return this->current_node_->element_;
        }

		Iterator& operator++() //TODO - is this really pre inc?
        {
            this->InOrder();
            return *this;
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

        Stack<Node*> nodes_;
		Node *node_pointer_;
		Node *current_node_;
		Node *previous_node_;
    private:

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
	};

	// Iterators over const and non-const sets:
	Iterator begin()
    {
        Iterator iter;

		iter.node_pointer_ = this->root_.get();
		iter.current_node_ = this->root_.get();
		return ++iter;
    }

	ConstIterator begin() const
    {
        Iterator iter;

		iter.node_pointer_ = this->root_.get();
		iter.current_node_ = this->root_.get();
		return ++iter;
    }

	Iterator end()
    {
        Iterator iter;
		iter.current_node_ = nullptr;
		return iter;
    }

	ConstIterator end() const
    {
        Iterator iter;
		iter.current_node_ = nullptr;
		return iter;
    }

	/**
	 * Look up a specific value within this set.
	 *
	 * This should return an iterator that is equal to end() if the value
	 * is not found.
	 */
	Iterator find(const T&) UNIMPLEMENTED
	ConstIterator find(const T&) const UNIMPLEMENTED

struct Node
	{
		// Did you know that structs can have methods too?
		Node(T &&value)
			: element_(std::move(value)), count_(1), left_(nullptr), right_(nullptr)
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
	void insert(T &&value, std::unique_ptr<Node> &node)
	{
		if (not node)
		{
			node = std::make_unique<Node>(std::move(value));
		}
		else if (compare_(value, node->element_))
		{
			insert(std::move(value), node->left_);
		}
		else if (compare_(node->element_, value))
		{
			insert(std::move(value), node->right_);
		}
		else
		{
			// ignore duplicates
		}
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

#endif