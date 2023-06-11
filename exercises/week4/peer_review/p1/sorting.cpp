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

#include <iostream>
#include <vector>
#include "sorting.h"

using namespace std;


int main(){
    // Test case
    vector<int> numbers = {170, 0, 75, 90, 802, 24, 2, 66, 543, 2, 1234, 56, 9, 130};
    cout << "Before sorting: ";
    for (int num : numbers) {
        cout << num << " ";
    }
    cout << endl;

    insertionSort(numbers.begin(), numbers.end());

    cout << "After sorting: ";
    for (int num : numbers) {
        cout << num << " ";
    }
    cout << endl;


    return 0;
}