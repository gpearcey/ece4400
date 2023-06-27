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

int main()
{
	BinarySearchTree<int> bst;

	bst.insert(4);
	bst.insert(2);
	bst.insert(7);

	std::cout << "min value: " << bst.min() << "\n";
	std::cout << "max value: " << bst.max() << "\n";

	//bst.print(std::cout);

	return 0;
}