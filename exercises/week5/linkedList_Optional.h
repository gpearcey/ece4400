#include <iostream>
#include <memory>

using namespace std;


/**
 * LinkedList Class
 * Still in progress, curently not functioning properly
*/

class LinkedList
{
public:
	LinkedList() : size_(0)
	{
        head_ = std::make_unique<Node>();
        tail_ = std::make_unique<Node>();
        head_->forward_ptr_ = tail_.get();
        tail_->backward_ptr_ = head_.get();
	}

    size_t size(){
        return size_;
    }     

    double front(){
        return (head_->forward_ptr_)->value_;
    }

    double back(){
        return (tail_->backward_ptr_)->value_;
    }

    void push_back(double v){
        std::unique_ptr<Node> n = std::make_unique<Node>();
        //set value of new node n
        n->value_ = v;

        //set last node's forward pointer to point to n
        (tail_->backward_ptr_)->forward_ptr_ = n.get();

        //set n's backward pointer to last node
        n->backward_ptr_ = tail_->backward_ptr_;

        //set tail's backward pointer to n
        tail_->backward_ptr_ = n.get();

        //set node's forward pointer to tail
        n->forward_ptr_ = tail_.get();

        double help = (head_->forward_ptr_)->value_ ;

        size_++;

        return;
    }

    void printNodes(){
        
    }

	size_t size() const
	{
		return size_;
	}
    ~LinkedList(){}

private:

    class Node
    {
    public:
        Node(){};
        Node* forward_ptr_;
        Node* backward_ptr_;
        double value_;
        ~Node(){
            delete forward_ptr_;

        }
    };

    size_t size_;
    std::unique_ptr<Node> head_;
    std::unique_ptr<Node> tail_;


};


