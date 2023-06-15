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

template<typename T>
class List
{
public:
	//! An iterator over the list
	class iterator
	{
	public:
		/**
		 * The dereference operator.
		 *
		 * @returns   a reference to the "current" element
		 */
		T& operator*();

		/**
		 * Pre-increment operator (i.e., `++i`).
		 *
		 * This method increments the iterator and then returns a
		 * reference to the newly-incremented iterator.
		 *
		 * @returns   a reference to this iterator, after incrementing
		 */
		iterator& operator++();

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
		iterator operator++(int ignored);

		//! Is this iterator pointing at the same place as another one?
		bool operator== (const iterator&) const;

		//! Is this iterator pointing at a different place from another?
		bool operator!= (const iterator&) const;
	};


	//! Default constructor
	List(){
		head_ = std::make_unique<Node>();
	}

	//! Copy constructor
	List(const List&);

	//! Move constructor
	List(List&&);

	//! Destructor
	~List(){
		while (head_.getNext() != nullptr){
			head_ = std::move(head_.getNext()); 
		}

	};

	//! Copy assignment operator
	List& operator= (const List&);

	//! Move assignment operator
	List& operator= (List&&);


	//
	// Accessors:
	//
	//! How many elements are in this list?
	size_t size() const;

	//! Is this list empty?
	bool empty() const;

	//! Get an iterator to the beginning of the list
	iterator begin();

	//! Get an iterator just past the end of the list
	iterator end();


	//
	// Mutators:
	//
	//! Copy an element to the front of the list
	void push_front(const T&);

	//! Move an element to the front of the list
	void push_front(T&&);

	//! Copy an element to the back of the list
	void push_back(const T&);

	//! Add an element to the back of the list
	void push_back(T&&);

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
	iterator insert(iterator, const T&);

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
	iterator insert(iterator, T&&);

	//! Remove an element from an arbitrary location
	void erase(iterator);

private:
	// Add whatever you need to add here

	class Node{
	public:
		Node() : next_(nullptr){};
		Node(T value) : value_(value), next_(nullptr){};

		T getValue(){
			return value_;
		};

		void setValue(T value){
			value_ = value;
			return;
		};

		std::unique_ptr<Node>& getNext(){
			return &next_;
		};

		void setNext(std::unique_ptr<Node>& next_node){
			next_ = std::move(next_node);
			return;
		};

		~Node(){
			//add cout
		};

	private:
		T value_;
		std::unique_ptr<Node> next_;
	};

	std::unique_ptr<Node> head_;
};