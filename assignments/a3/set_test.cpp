#include <iostream>
#include "Set.hh"

using namespace std;
//testing stack
/*
int main()
{
	
	Stack<int> s;

	s.push(5);
	s.push(3);
	s.push(8);

	for (auto i = s.begin(); i != s.end(); ++i)
	{
		cout << *i << "\n";
	}
	std::cout << s.top() << std::endl;
	s.pop();
	std::cout << s.top() << std::endl;
	cout << "\n" ;
}*/


int main()
{
	Set<int> t;
	for (int i = 50; i<151;i++)
	{
		t.insert(i);
	}
	Set<int> t2;
	for (int j = 100; j<201;j++)
	{
		t2.insert(j);
	}

	Set<int> t3 = t.intersection(t2);
	for (auto i = t3.begin(); i != t3.end(); ++i)
	{
		cout << *i << "\n";
	}

	t3.remove(133);
	for (auto i = t3.begin(); i != t3.end(); ++i)
	{
		cout << *i << "\n";
	}

	auto k = t3.find(100);
	cout << *k << endl;
	//for (int n : {5,4,2})
	//{
	//	t2.insert(n);
	//}
	//t2.insert(5);
	//Set<int> t3 = t.setUnion(t2);
//
	////auto i = t.begin();
	////cout << *i << "\n";
//
	//for (auto i = t3.begin(); i != t3.end(); ++i)
	//{
	//	cout << *i << "\n";
	//}
	//auto h = t3.find(5);
	//cout << *h << endl;
	//cout << "\n" ;
	//
	//Set<int> t2 = t;
//
//
	////for (auto j = t2.begin(); j != t2.end(); ++j)
	////{
	////	cout << *j << "\n";
	////}
	////cout << "\n" ;
//
	//Set<int> t3 = std::move(t2);
	//for (auto j = t3.begin(); j != t3.end(); ++j)
	//{
	//	cout << *j << "\n";
	//}
	//cout << "\n" ;
	//cout << t3.contains(5438) << endl;
//
	Set<std::basic_string<char>> s;
	s.insert("grace");
	s.insert("mike");
	s.insert("madison");
	s.insert("abby");
	auto i = s.find("abby");
	for (auto i = s.find("grace"); i != s.end(); ++i)
	{
		cout << *i << "\n";
	}
	const auto j = s.find("grace");

	//cout << *j << endl;
//
	return 0;

    //CheckInt(22, *s.find(22));
    //Check(s.find(99) == s.end(), "find(99) should equal end()");
}