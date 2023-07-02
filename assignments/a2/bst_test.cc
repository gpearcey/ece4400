#include <iostream>
#include "BST.h"

using namespace std;

int main(){
	// Create a tree of integers:
	BinarySearchTree<int> t;

	// Fancy way of not having to write BinarySearchTree<int> twice:
	const auto Order = decltype(t)::Traversal::PreOrder;
//
	//// Insert the values 4, 2, 6, 1, 3, 5 and 7:
	for (int n : { 4, 2, 6, 1, 3, 5, 7 })
	{
		t.insert(n);
	}
//
	//// The following should print: 1234567
	int count = 0;
	for (auto i = t.begin(Order); i != t.end(); i++)
	{
		if (i.iterator_node_ == nullptr){
			cout << "i is null" << endl;
		}
		cout << *i << " ";
		//cout << "count: " << count << endl;
		count++;
	}
	cout << "\n" ;

};

