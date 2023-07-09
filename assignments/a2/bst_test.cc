#include <iostream>
#include "BST.h"

using namespace std;

/* Checking Preorder with integers*/

int main(){
	// Create a tree of integers:
	BinarySearchTree<int> t;

	// Fancy way of not having to write BinarySearchTree<int> twice:
	const auto Order = decltype(t)::Traversal::PreOrder;

	//// Insert the values 4, 2, 6, 1, 3, 5 and 7:
	for (int n : { 4, 2, 6, 1, 3, 5, 7 })
	{
		t.insert(n);
	}

	//// The following should print: 1234567
	for (auto i = t.begin(Order); i != t.end(); i++)
	{
		cout << *i << " ";
	}
	cout << "\n" ;
};


/* Checking Preorder with unique pointers */

//int main() {
//
//	// Create a tree of integers:
//	BinarySearchTree<unique_ptr<int>> t;
//	// Fancy way of not having to write BinarySearchTree<int> twice:
//	const auto Order = decltype(t)::Traversal::PreOrder;
//	//// Insert the values 4, 2, 6, 1, 3, 5 and 7:
//
//	std::unique_ptr<int> ptr0(new int(9));
//	std::unique_ptr<int> ptr1(new int(3));
//	std::unique_ptr<int> ptr2(new int(4));
//	std::unique_ptr<int> ptr3(new int(0));
//	std::unique_ptr<int> ptr4(new int(1));
//	std::unique_ptr<int> ptr5(new int(32));
//	std::unique_ptr<int> ptr6(new int(17));
//
//	t.insert(std::move(ptr3));
//	t.insert(std::move(ptr5));
//	t.insert(std::move(ptr2));
//	t.insert(std::move(ptr4));
//	t.insert(std::move(ptr6));
//	t.insert(std::move(ptr1));
//	t.insert(std::move(ptr0));
//
//
//	//// The following should print: 1234567
//	for (auto i = t.begin(Order); i != t.end(); i++)
//	{
//		cout << *(*i) << " ";
//	}
//	cout << "\n" ;
//
//	return 0;
//
//};



/* Checking InOrder Traversal*/
/*
int main(){


	BinarySearchTree<int> t;

	const auto Order = decltype(t)::Traversal::InOrder;

	for (int n : { 4, 2, 6, 1, 3, 5, 7 })
	{
		t.insert(n);
	}

	for (auto i = t.begin(Order); i != t.end(); i++)
	{
		cout << *i << " ";
	}
	cout << "\n" ;
	

	BinarySearchTree<unique_ptr<int>> t1;

	const auto Order1 = decltype(t1)::Traversal::InOrder;

	std::unique_ptr<int> ptr0(new int(9));
	std::unique_ptr<int> ptr1(new int(3));
	std::unique_ptr<int> ptr2(new int(4));
	std::unique_ptr<int> ptr3(new int(0));
	std::unique_ptr<int> ptr4(new int(1));
	std::unique_ptr<int> ptr5(new int(32));
	std::unique_ptr<int> ptr6(new int(17));
	t1.insert(std::move(ptr3));
	t1.insert(std::move(ptr5));
	t1.insert(std::move(ptr2));
	t1.insert(std::move(ptr4));
	t1.insert(std::move(ptr6));
	t1.insert(std::move(ptr1));
	t1.insert(std::move(ptr0));

	for (auto i = t1.begin(Order1); i != t1.end(); i++)
	{
		cout << *(*i) << " ";
	}
	cout << "\n" ;
	return 0;
}
*/

/* Checking PostOrder Traversal*/

//int main(){
//
//
//	BinarySearchTree<int> t;
//
//	const auto Order = decltype(t)::Traversal::PostOrder;
//
//	for (int n : { 4, 2, 6, 1, 3, 5, 7 })
//	{
//		t.insert(n);
//	}
//
//	for (auto i = t.begin(Order); i != t.end(); i++)
//	{
//		cout << *i << " ";
//	}
//	cout << "\n" ;
//
//	BinarySearchTree<int> t1;
//
//	const auto Order1 = decltype(t1)::Traversal::PostOrder;
//
//	for (int n : { 3, 2, 1, 0, 5, 4, 6 })
//	{
//		t1.insert(n);
//	}
//
//	for (auto j = t1.begin(Order1); j != t1.end(); j++)
//	{
//		cout << *j << " ";
//	}
//	cout << "\n" ;
	

	//BinarySearchTree<unique_ptr<int>> t1;
//
	//const auto Order1 = decltype(t1)::Traversal::InOrder;
//
	//std::unique_ptr<int> ptr0(new int(9));
	//std::unique_ptr<int> ptr1(new int(3));
	//std::unique_ptr<int> ptr2(new int(4));
	//std::unique_ptr<int> ptr3(new int(0));
	//std::unique_ptr<int> ptr4(new int(1));
	//std::unique_ptr<int> ptr5(new int(32));
	//std::unique_ptr<int> ptr6(new int(17));
	//t1.insert(std::move(ptr3));
	//t1.insert(std::move(ptr5));
	//t1.insert(std::move(ptr2));
	//t1.insert(std::move(ptr4));
	//t1.insert(std::move(ptr6));
	//t1.insert(std::move(ptr1));
	//t1.insert(std::move(ptr0));
//
	//for (auto i = t1.begin(Order1); i != t1.end(); i++)
	//{
	//	cout << *(*i) << " ";
	//}
	//cout << "\n" ;
//	return 0;
//}

