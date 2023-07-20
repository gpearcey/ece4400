#include <iostream>
#include "Set.hh"

using namespace std;

int main()
{
	Set<int> t;

	for (int n : { 4, 2, 6, 1, 3, 5, 7 })
	{
		t.insert(n);
	}

	for (auto i = t.begin(); i != t.end(); ++i)
	{
		cout << *i << "gfhs ";
	}
	cout << "\n" ;
	

    //Set<unique_ptr<int>> t1;
//
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
	//for (auto i = t1.begin(); i != t1.end(); ++i)
	//{
	//	cout << *(*i) << " ";
	//}
	//cout << "\n" ;
	return 0;

    //CheckInt(22, *s.find(22));
    //Check(s.find(99) == s.end(), "find(99) should equal end()");
}
