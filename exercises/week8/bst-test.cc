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

#include "BST.h"

#include <iostream>
using namespace std;

int main()
{
	BinarySearchTree<int> bst;
	cout << bst.empty() << endl;


	bst.insert(4);
	bst.insert(2);
	bst.insert(2);
	bst.insert(7);
	bst.insert(1);
	bst.insert(99);
	bst.insert(3);
	bst.insert(-44);
	bst.insert(100);
	bst.insert(101);
	bst.insert(102);

	std::cout << "max value: " << bst.max() << "\n";
	std::cout << "min value: " << bst.min() << "\n";
	
	//bst.print(std::cout);

	std::cout << "Tree contains 8 is " << bst.contains(8) << endl;
	std::cout << "Tree contains 99 is " << bst.contains(99) << endl;

	cout << "The max depth of this tree is " << bst.maxDepth() << endl;

	bst.print();
	
	return 0;
}