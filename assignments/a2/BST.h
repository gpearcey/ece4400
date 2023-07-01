/*
 * Copyright 2018-2019 Jonathan Anderson
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

#include <cassert>
#include <cstddef>      // for definition of size_t
#include <functional>   // std::function
#include <memory>       // std::unique_ptr
#include <stack>        // std::stack

template<typename T, typename Comparator = std::less<T>>
class BinarySearchTree
{
public:
    struct Node; //forward declaration
	enum class Traversal
	{
		PreOrder,
		InOrder,
		PostOrder,
	};

	//! Insert a new value into the appropriate place in the tree.
	void insert(T value)
	{
		insert(std::move(value), root_);
	}

	void dot(std::ostream &o) const
	{
		o << "digraph {\n";

		if (root_)
		{
			root_->dot(o);
		}

		o << "}\n";
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
        
		Iterator operator ++ (int){
            if (this->order_ == PreOrder){

            }
            else if (this->order_ == InOrder){

            }
            else if (this->order == PostOrder){

            }
            return this;
        }

		//! Dereference the iterator at its current position
		const T& operator * (){
            return this->node_pointer_->element_;
        }

		//! Is this iterator *not* the same as another?
		bool operator != (const Iterator &other);

		// add whatever else you need here
        std::stack<std::unique_ptr<Node>> nodes_;
        Node* node_pointer_;
        Traversal order_;

    private:
        PreOrder(){
            nodes_.push(node_pointer_);
                if (node_pointer_->left_ == nullptr && node_pointer_->right_ == nullptr){ //if node has no children
                    nodes_.pop();
                    if (nodes_.front()->left_ == this->node_pointer_){
                        //this node is the left child
                        if (nodes_.front()->right){
                            //if the parent node has a right child
                            node_pointer_ = nodes_.front(); //set the pointer to the right child
                            nodes_.push(node_pointer_); // add the right child to the stack
                            return this;
                        }
                        PreOrder(this); //recurse up the tree
                    }
                    else if (nodes_.front()->right_ == this->node_pointer_){
                        //this node is the right child
                        if(nodes_.size() == 1){
                            //we've reached the end
                            return nullptr;
                        }
                        PreOrder(nodes_.front()); //recurse up the tree
                    }
                }
                else if(node_pointer_->left_ == nullptr){
                    //node only has a right child
                    node_pointer_ = node_pointer_->right_; //go to the right child
                    nodes_.push(node_pointer_);
                    return this;
                }
                else if(node_pointer_->right_ == nullptr){
                    //node only has a left child
                    node_pointer_ = node_pointer_->left_; //go to the left child
                    nodes_.push(node_pointer_);
                    return this;
                }
                else if(node_pointer_->left != nullptr and node_pointer->right_ != nullptr){
                    // node has 2 children
                    node_pointer_ = node_pointer->left; //go to the left child
                    nodes_.push(node_pointer_);
                    return this;
                }
        }


	};

    /**
     * Returns an iterator that can be used to traverse the tree in the given order.
     *
     * This iterator should visit every node in the tree exactly once, after which
     * it should test equal to the iterator returned from `end()`.
     */
	Iterator begin(Traversal order){
        Iterator iter;
        iter.order_ = order;
        if (order == Traversal::PreOrder){
            iter.node_pointer_ = this->root_;
        }
        else if (order == Traversal::InOrder){

        }
    }
    /**
     * The end of a tree traversal.
     *
     * The iterator returned by this method should be usable as the end-of-iteration
     * marker for any iterator on this tree, whether it was traversing the tree in
     * pre-, in- or post-order.
     */
	Iterator end(){
        return nullptr;
    }

private:
	struct Node
	{
		Node(T value) : element_(std::move(value))
		{
		}

		void dot(std::ostream &o) const
		{
			// NOTE: this is slightly more complicated than strictly
			//       necessary (using addresses as names, etc.), but
			//       it will produce valid Dot output even when the
			//       node values are things like money (e.g., $17)

			o
				<< "  \"" << this << "\""
				<< " [ label = \"" << element_ << "\" ];\n";

			if (left_)
			{
				o
					<< "  \"" << this << "\""
					<< " -> "
					<< "\"" << left_.get() << "\""
					<< " [ label = \"L\" ]\n";

				left_->dot(o);
			}

			if (right_)
			{
				o
					<< "  \"" << this << "\""
					<< " -> "
					<< "\"" << right_.get() << "\""
					<< " [ label = \"R\" ]\n";

				right_->dot(o);
			}
		}

		T element_;
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
			// assuming no duplicates
		}
	}

	Comparator compare_;
	std::unique_ptr<Node> root_;
};