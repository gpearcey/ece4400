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
	BinarySearchTree<int> bst;
	cout << bst.empty() << endl;


	bst.insert(10);
	bst.insert(5);
	bst.insert(15);
	bst.insert(20);
	bst.insert(30);
	bst.insert(35);
	bst.insert(21);
	bst.insert(22);


	//std::cout << "max value: " << bst.max() << "\n";
	//std::cout << "min value: " << bst.min() << "\n";
//
	//std::cout << "Tree contains 8 is " << bst.contains(8) << endl;
	//std::cout << "Tree contains 99 is " << bst.contains(99) << endl;
//
	//cout << "The max depth of this tree is " << bst.maxDepth() << endl;
//
	//cout << "Height of the tree is " << bst.root_->left_->height_ << endl;

    //std::ofstream file("bst.dot");
    //if (file.is_open()) {
    //    bst.printDot(file);
    //    file.close();
    //}

	//bst.printDot(std::cout);
	return 0;
}