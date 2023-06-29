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

//TODO:
// print
// remove
//comment

#include <cassert>
#include <cstddef>      // for definition of size_t
#include <functional>   // std::function
#include <memory>       // std::unique_ptr
#include <iostream>
#include <vector>
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

	void print(){
		int depth = this->maxDepth();
		std::vector<std::vector<T>> values_to_print;
		values_to_print.resize(depth + 1); //root needs to be stored too
		this->root_->print(values_to_print, depth);
		for (int i = values_to_print.size() - 1; i >= 0; --i){
			for (const T& value : values_to_print[i]){
				cout << value << "  ";
			}
			cout << endl;
		}
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
				//cout << "red" << endl;
				return current_min;
			}

			if (compare(node->value(),  current_min->value())) {
				//cout << "white" << endl;
        		current_min = node;
    		}
    		Node* left_min = find_min(node->left_.get(), current_min, compare);
    		Node* right_min = find_min(node->right_.get(), current_min, compare);

    		if (left_min != nullptr &&  compare(left_min->value(), current_min->value())) {
    		   // cout << "yellow" << endl;
				current_min = left_min;
    		}

    		if (right_min != nullptr &&  compare(right_min->value(), current_min->value())) {
    		    //cout << "black" << endl;
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
				//cout << "green" << endl;
				return current_max;
			}
   
   			if (compare(current_max->value(), node->value() )) {
				//cout << "blue" << endl;
        		current_max = node;
    		}
    		Node* left_max = find_max(node->left_.get(), current_max, compare);
    		Node* right_max = find_max(node->right_.get(), current_max, compare);

    		if (left_max != nullptr &&  compare(current_max->value(), left_max->value()) ) {
    		    //cout << "purple" << endl;
				current_max = left_max;
    		}

    		if ( right_max != nullptr && compare(current_max->value(),right_max->value() )) {
    		    //cout << "pink" << endl;
				current_max = right_max;
    		}

    		return current_max;
        }

		int print(std::vector<std::vector<T>>& values_vec, int prev_height){
			if (this ==  nullptr){
				//cout << "water" << endl;
				return prev_height;
			}
			//cout << "egg" << endl;
			//int node_depth = this->maxDepth() - 1;
			//cout << "node value is: " << this->value() << " and node depth is: " << node_depth << endl;

			values_vec[prev_height].push_back(this->value());
			//cout << "sugar" << endl;
    		if (this->left_ != nullptr){
				//cout << "cinnamon" << endl;
				this->left_->print(values_vec, prev_height-1);
			}   		    

    		if (this->right_ != nullptr){
				this->right_->print(values_vec, prev_height-1);
			}    		    
			//cout << "salt" << endl;
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
	 */
	void insert(T &&value, std::unique_ptr<Node> &node){
		if (compare_(value, node->value())){ 
			//std::cout << "apple" << endl;
			if (node->left_ == nullptr){
				//cout << "blueberry" << endl;
				std::unique_ptr<Node> new_node = std::make_unique<Node>(std::move(value));
				node->left_ = std::move(new_node);
			}
			else{
				//cout << "orange" << endl;
				insert(std::move(value), node->left_);
			}			
		}
		else if (compare_(node->value(), value)){
			//cout << "banana" << endl;
			if (node->right_ == nullptr){
				//cout << "grape" << endl;
				std::unique_ptr<Node> new_node = std::make_unique<Node>(std::move(value));
				node->right_ = std::move(new_node);
			}
			else{
				//cout << "pie" << endl;
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