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
#include <cmath>

/**
 * insertionSort
*/
template<typename Iter, typename Comparator>
void insertionSort(const Iter& begin, const Iter& end, Comparator compareFn)
{
    for (auto i = next(begin,1); i != end; i++){
        auto key = std::move(*i);
    	auto j = prev(i,1);
    	while (j >= begin && compareFn(*j, key)){
    	    *(next(j,1)) = std::move(*j);
    	    j--;
    	}
		*(next(j,1)) = std::move(key);
    }
}

/**
 * getDigit
 * Helper function for radixSort
 * Returns the digit of a value for processing
*/
template<typename T>
int getDigit(T v, int digit_place_){
	auto power = std::pow(10,(digit_place_ + 1));
	int int_power = static_cast<int>(power);
	int remainder = v % int_power;
	int floor = std::floor(remainder / std::pow(10, digit_place_));

	return floor;
}

/**
 * radixSort with iterators
 * Currently only implemented for integers
*/
template<typename Iter>
void radixSort(const Iter& begin, const Iter& end){

	const int len = std::distance(begin, end);//gets the length of the array to be sorted

	int numBuckets = 10;//number of buckets needed to sort integers

	std::vector<std::vector<int>> buckets(numBuckets);//store a bucket for each digit in buckets vector
	
	int digit_place = 0;

	while (buckets[0].size() < len){ //values are sorted when all elements in array are in bucket0, i.e. there are no more digits to sort	
		
		// empty the buckets from the previous loop
		for (int i=0; i<10; i++){
			buckets[i].clear(); 
		}

		// fill buckets
		for (auto j = begin; j != end; j++) {
			int digit = getDigit(*j, digit_place); //returns the digit we want to sort by
			buckets[digit].push_back(*j);
		}		

		//fill values from buckets
		auto k = begin;
		for (int i = 0; i < numBuckets; i++){
			for(auto element : buckets[i]){
				*k = element;
				k++;
			}
		}
		digit_place++; //sort by the next digits place
	}

	//move the values in bucket0 to values
	auto l = begin; 
	for (int m = 0; m < len; m++ ){
		*l = buckets[0][m];
		l++;
	}

	return;
}

