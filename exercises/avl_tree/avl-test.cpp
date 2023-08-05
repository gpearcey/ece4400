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

#include "AVL.h"

#include <iostream>
#include <ostream>
using namespace std;

int main()
{
	AVLTree<int> avl;
	cout << avl.empty() << endl;


	avl.insert(10);
	avl.insert(5);
	avl.insert(15);
	avl.insert(50);
	avl.insert(20);
	avl.insert(30);
	avl.insert(35);
	avl.insert(21);
	avl.insert(22);
//
//
	//std::cout << "max value: " << avl.max() << "\n";
	//std::cout << "min value: " << avl.min() << "\n";
//
	//std::cout << "Tree contains 8 is " << avl.contains(8) << endl;
	//std::cout << "Tree contains 99 is " << avl.contains(99) << endl;
//
	//cout << "The max depth of this tree is " << avl.maxDepth() << endl;
//
	//cout << "Height of the tree is " << avl.root_->right_->height_ << endl;
//
	avl.printDot(std::cout);
	return 0;
}