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
using namespace std;
template<typename T, typename Comparator = std::less<T>>
class BinarySearchTree
{
public:
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

		return root_->maxDepth();
	}

	//! Is this tree empty?
	bool empty() const
	{
		return (not root_);
	}

	//! Insert a new value into the appropriate place in the tree.
	void insert(T value)
	{
		cout << "1" << endl;
		if (this->empty()){
			cout << "2" << endl;
			std::unique_ptr<Node> new_node = std::make_unique<Node>(std::move(value));
			this->root_ = std::move(new_node);
			cout << "3" << endl;
		}

		else{
			cout << "4" << endl;
			insert(std::move(value), root_);
			cout << "5" << endl;
		}
		
		
	}

	/**
	 * Find the minimum value in the tree.
	 *
	 * @pre   tree is not empty
	 */
	const T& min() const
	{
		assert(root_);
		return root_->min().value();
	}

	/**
	 * Find the minimum value in the tree.
	 *
	 * @pre   tree is not empty
	 */
	const T& max() const
	{
		assert(root_);
		return root_->max().value();
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

private:
	struct Node
	{
		// Did you know that structs can have methods too?
		Node(T &&value)
			: element_(value), count_(1), left_(nullptr), right_(nullptr)
		{
		}

		const T& value() const { return element_; }

		bool contains(const T&) const;
		Node& min(){
            Node* current_min = this;
            current_min = find_min(this, current_min);
            return *current_min;            
        };

        Node* find_min(Node* node, Node* current_min){
			if (node == nullptr){
				cout << "red" << endl;
				return current_min;
			}

			if (node->value() < current_min->value()) {
				cout << "white" << endl;
        		current_min = node;
    		}
    		Node* left_min = find_min(node->left_.get(), current_min);
    		Node* right_min = find_min(node->right_.get(), current_min);

    		if (left_min != nullptr && left_min->value() < current_min->value()) {
    		    cout << "yellow" << endl;
				current_min = left_min;
    		}

    		if (right_min != nullptr && right_min->value() < current_min->value()) {
    		    cout << "black" << endl;
				current_min = right_min;
    		}

    		return current_min;
        }

		Node& max(){
            Node* current_max = this;
            current_max = find_max(this, current_max);
            return *current_max;      
		}

		Node* find_max(Node* node, Node* current_max){
			if (node == nullptr){
				cout << "green" << endl;
				return current_max;
			}
   
   			if (node->value() > current_max->value()) {
				cout << "blue" << endl;
        		current_max = node;
    		}
    		Node* left_max = find_max(node->left_.get(), current_max);
    		Node* right_max = find_max(node->right_.get(), current_max);

    		if (left_max != nullptr && left_max->value() > current_max->value()) {
    		    cout << "purple" << endl;
				current_max = left_max;
    		}

    		if (right_max != nullptr && right_max->value() > current_max->value()) {
    		    cout << "pink" << endl;
				current_max = right_max;
    		}

    		return current_max;
        }

		T takeMin();
		size_t maxDepth() const;

		T element_;
		size_t count_;
		std::unique_ptr<Node> left_;
		std::unique_ptr<Node> right_;
	};

	/**
	 * Internal implementation of recursive insert.
	 *
	 * @param   value      the value to insert
	 * @param   node       the root of the (sub-)tree being inserted into;
	 *                     may be null if the (sub-)tree is empty
	 * @todo not inserting larger numbers properly
	 */
	void insert(T &&value, std::unique_ptr<Node> &node){
		if (value < node->value()){ 
			//std::cout << "apple" << endl;
			if (node->left_ == nullptr){
				cout << "blueberry" << endl;
				std::unique_ptr<Node> new_node = std::make_unique<Node>(std::move(value));
				node->left_ = std::move(new_node);
			}
			else{
				cout << "orange" << endl;
				insert(std::move(value), node->left_);
			}			
		}
		else if (node->value() > value){
			cout << "banana" << endl;
			if (node->right_ == nullptr){
				cout << "grape" << endl;
				std::unique_ptr<Node> new_node = std::make_unique<Node>(std::move(value));
				node->right_ = std::move(new_node);
			}
			else{
				cout << "pie" << endl;
				insert(std::move(value), node->right_);
			}
			
		}
		else {
			node->count_++;
		}

		return;
	}

	/**
	 * Internal implementation of recursive removal.
	 *
	 * @param   value      the value to remove
	 * @param   node       the root of the (sub-)tree being inserted into;
	 *                     may be null if the (sub-)tree is empty
	 */
	bool remove(const T &value, std::unique_ptr<Node> &node);

	Comparator compare_;
	std::unique_ptr<Node> root_;
};