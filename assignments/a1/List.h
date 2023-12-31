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

#include <cstdint>
#include <cstddef>
#include <memory>
#include <iostream>
using namespace std;

template<typename T>
class List
{
public:
	class Node; //forward declaration

	//! An iterator over the list
	class iterator
	{
	public:
		/**
		 * The dereference operator.
		 *
		 * @returns   a reference to the "current" element
		 */
		T operator*(){
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
		iterator& operator++(){
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
		iterator operator++(int ignored){
			iterator i = *this;
            ++*this;						
			return i;
		}

		//! Is this iterator pointing at the same place as another one?
		bool operator== (const iterator& other) const{
			if (this->node_pointer_ == other.node_pointer_){
				return true;
			}
			else{
				return false;
			}
		};

		//! Is this iterator pointing at a different place from another?
		bool operator!= (const iterator& other) const{
			if (this->node_pointer_ == other.node_pointer_){
				return false;
			}
			else{
				return true;
			}
		}

		Node* node_pointer_;		
	};


	//! Default constructor
	List(){
		head_ = std::make_unique<Node>();
	};

	//! Copy constructor
	List(const List& other){
		head_ = std::make_unique<Node>();
		this->head_ = std::make_unique<Node>(*other.head_);

	};

	//! Move constructor
	List(List&& other){
		head_ = std::make_unique<Node>();
		if (this != &other) {
			this->head_->next_ = std::move(other.head_->next_);
		}
	};

	//! Destructor
	~List(){};

	//! Copy assignment operator
	List& operator= (const List& other){
        this->head_ = std::make_unique<Node>(*other.head_);
		return *this;
	}

	//! Move assignment operator
	List& operator= (List&& other){
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
			Node* current_node = head_->getNext();
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
	iterator begin(){
		iterator i;
		i.node_pointer_ = this->head_->getNext();
		return i;

	};

	//! Get an iterator just past the end of the list
	iterator end(){
		iterator i;
		//set last node to point to the new node

		if (head_->getNext() == nullptr){
			i.node_pointer_ = head_.get();
		}else{
			//traverse through the list until the last node is reached
			Node* current_node = head_->getNext();
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
	void push_front(const T& value){

		//create new node
		std::unique_ptr<Node> new_node = std::make_unique<Node>(value);
		
		//set new node's next pointer to the node that used to be at the front if list is not empty
		if (head_->getNext() != nullptr){	
			new_node->setNext(this->head_->next_);
		}

		//set the head to point to the new node
		this->head_->setNext(new_node);
		return;
	};

	//! Move an element to the front of the list
	void push_front(T&& value){
		std::unique_ptr<Node> new_node = std::make_unique<Node>(std::move(value));		

		//set new node's next pointer to the node that used to be at the front if list is not empty
		if (head_->getNext() != nullptr){	
			new_node->setNext(this->head_->next_);
		}

		//set the head to point to the new node
		this->head_->setNext(new_node);
		return;
	};

	//! Copy an element to the back of the list
	void push_back(const T& value){
		
		//create new node
		std::unique_ptr<Node> new_node = std::make_unique<Node>(value);
		
		//set last node to point to the new node
		if (head_->getNext() == nullptr){ //set the head to point to new node if the list is empty
			head_->setNext(new_node);
		}else{
			//traverse through the list until the last node is reached
			Node* current_node = head_->getNext();
			while (current_node->getNext() != nullptr){
				current_node = current_node->getNext();
			}
			//set the last node to point to the new node
			current_node->setNext(new_node);
		}

		return;
	};

	//! Add an element to the back of the list
	void push_back(T&& value){
		//create new node
		std::unique_ptr<Node> new_node = std::make_unique<Node>(std::move(value));
		
		//set last node to point to the new node
		if (head_->getNext() == nullptr){ //set the head to point to new node if the list is empty
			head_->setNext(new_node);
		}else{
			//traverse through the list until the last node is reached
			Node* current_node = head_->getNext();
			while (current_node->getNext() != nullptr){
				current_node = current_node->getNext();
			}
			//set the last node to point to the new node
			current_node->setNext(new_node);
		}

		return;
	};

	/**
	 * Copy an element into an arbitrary location.
	 *
	 * This method makes a copy of an element and inserts that copy into a
	 * location pointed at by the given iterator. After insertion into a
	 * list of n elements, the list should contain n+1 elements (i.e., no
	 * existing element should be replaced).
	 *
	 * @returns   an iterator pointing at the newly-inserted element
	 */
	iterator insert(iterator iter, const T& value){

		//create new node
		std::unique_ptr<Node> new_element = std::make_unique<Node>(std::move(value));	

		//set new node to point to where iterator points to

		if (new_element->getNext() == head_->getNext()) { //new node is set to be insert at the head
			new_element->setNext(head_->next_);
			head_->setNext(new_element);
			iter.node_pointer_ = head_->getNext();
		} 
		else {
			//traverse through the list until we've reached where the iterator is pointing to
			Node* current_node = head_->getNext();
			while (current_node->getNext() != iter.node_pointer_){				
				current_node = current_node->getNext();				
			}
			//add the new node at the specified location
			new_element->setNext(current_node->next_);			
			current_node->setNext(new_element);
			iter.node_pointer_ = current_node->getNext(); //update the iterator to point to the newly inserted node		
		}	
			
		return iter;
	}

	/**
	 * Move an element into an arbitrary location.
	 *
	 * This method inserts an element into a location pointed at by the
	 * given iterator, using move semantics to avoid copies. After insertion
	 * into a list of n elements, the list should contain n+1 elements
	 * (i.e., no existing element should be replaced).
	 *
	 * @returns   an iterator pointing at the newly-inserted element
	 */
	iterator insert(iterator iter, T&& value){

		//create new node
		std::unique_ptr<Node> new_element = std::make_unique<Node>(std::move(value));	

		//set new node to point to where iterator points to
		if (iter.node_pointer_ == head_->getNext()) {//new node is set to be insert at the head
			new_element->setNext(head_->next_);
			head_->setNext(new_element);
			iter.node_pointer_ = head_->getNext();
		} 
		else {
			//traverse through the list until we've reached where the iterator is pointing to
			Node* current_node = head_->getNext();
			while (current_node->getNext() != iter.node_pointer_){
				
				current_node = current_node->getNext();				
			}
			//add the new node at the specified location
			new_element->setNext(current_node->next_);			
			current_node->setNext(new_element);

			iter.node_pointer_ = current_node->getNext(); //update the iterator to point to the newly inserted node	
			
		}	
			
		return iter;
	}

	//! Remove an element from an arbitrary location
	void erase(iterator iter){
		//Don't erase if list is empty
		if (iter.node_pointer_ == nullptr) {
			std::cout << "Invalid iterator, can't erase element." << std::endl;
			return;
		}
		
		if (iter.node_pointer_ == head_->getNext()) {
			head_->setNext(iter.node_pointer_->next_);//erase first element if only one element in list
		} 
		else {
			//erase element iterator points to
			Node* current_node = head_->getNext();
			while (current_node->getNext() != iter.node_pointer_){
				current_node = current_node->getNext();
			}
			current_node->setNext(iter.node_pointer_->next_);
			iter.node_pointer_ = iter.node_pointer_->getNext();		
		}
		return;
	}


	//! Represents a list element - contains a value and a pointer to the next element
	class Node{
	public:
		//! Default constructor
		Node() : next_(nullptr){};

		//! Constructor to initialize with a value
		Node(T value) : value_(std::move(value)), next_(nullptr){};

		//! Copy constructor
		Node(const Node& other): value_(other.value_), next_(nullptr){
    		if (other.next_) {
    		    next_ = std::make_unique<Node>(*other.next_);
    		}
		};

		//! Move constructor
		Node(Node&& other) : value_(std::move(other.value_)), next_(nullptr){
    		if (other.next_) {
    		    next_ = std::move(other.next_);
    		}
		};

		//
		// Accessors:
		//
		T getValue(){
			return value_;
		};

		Node* getNext(){
			return next_.get();
		};

		//
		// Mutators:
		//		
		void setValue(T value){
			value_ = std::move(value);
			return;
		};
		
		void setNext(std::unique_ptr<Node>& next_node){
			next_ = std::move(next_node);
			return;
		};

		//! Destructor
		~Node(){};

		// Pointer to next element
		std::unique_ptr<Node> next_;

	private:
		// Value of element
		T value_;
		
	};
private:
	// Represents the head of the list
	std::unique_ptr<Node> head_;
};