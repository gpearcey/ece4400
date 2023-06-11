/*
 * Copyright 2018-2019 Jonathan Anderson
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

#include <cassert>
#include <memory>
#include <string>
#include <vector>

/**
 * Adds two values together
 * 
 * @returns sum
*/
template<typename T>
T add(T x, T y)
{
	return x + y;
}

/**
 * Calculate the average of a set of values.
 *
 * @returns the arithmetic mean of the values, or 0 if `values`.size() == 0
 */
template<typename T>
T average(std::vector<T> values)
{
	if (values.empty()) 
	{
		//error if string vector
		return 0;
	}

	T sum;
	
	for (T v : values)
	{
		sum = add(sum, v);
	}

	return sum / values.size();
}

/**
 * Operator Overload for adding strings, processes them as doubles
 * 
 * @returns sum as a string
*/
std::string operator+(const std::string& x, const std::string& y)
{
	double x_double;

	try {
    	x_double = std::stod(x); //will not work if x has not been given a value yet 
    } catch (std::exception& e) {
        x_double = 0; //sets x to 0 if it does not have a value 
    }

	double y_double = std::stod(y);
	double sum = x_double + y_double;
    return std::to_string(sum); //convert result back to string

}

/**
 * Operator overload for diving a string by an int, processes both values as doubles
 * 
 * @returns quotient as a string
 */
std::string operator/(const std::string& x, const int y)
{
	double x_double = std::stod(x);

	double quotient = x_double / static_cast<double>(y);
    return std::to_string(quotient); //convert result back to string
}



/**
 * A data structure that holds a growable array, with the optimization that
 * small arrays are stored directly in the object rather than allocated from
 * the heap.
 */
template<typename T, int smallArraySize>
class GrowableArray
{
public:
	GrowableArray()
		: capacity_(8), size_(0)
	{
	}

	//! Add a value to the back of the array
	GrowableArray& operator << (T value)
	{
		if (size_ >= capacity_)
		{
			size_t newCapacity = 2 * capacity_;
			std::unique_ptr<T> bigger(new T[newCapacity]);

			// To be really clever, change this to std::copy():
			for (size_t i = 0; i < size_; i++)
			{
				bigger.get()[i] = (*this)[i];
			}

			largeArray_.swap(bigger);
			capacity_ = newCapacity;
		}

		size_ += 1;
		(*this)[size_ - 1] = value;

		return *this;
	}

	//! Access an element within the array
	T& operator[] (size_t index)
	{
		assert(size_ <= capacity_);

		if (index >= size_)
		{
			// TODO: real error handling?
			throw std::string("eek!");
		}

		if (largeArray_)
		{
			return largeArray_.get()[index];
		}
		else
		{
			return smallArray_[index];
		}
	}
	
	/**
	 * Calculates average of a GrowableArray
	 * Works for string types unless GrowableArray is empty
	 * 
	 * @returns average
	*/
	T average()
	{
		if (size_ == 0) 
		{
			//error if string vector
			return 0;
		}
		
		T sum;

		if (largeArray_) //check if large array has been set
		{
			for (int i = 0; i < size_; i++) {
				sum = add(sum,largeArray_.get()[i]);
			}
			return sum / size_;
		}
		else //we haven't surpassed small array capacity yet
		{
			for (int i = 0; i < size_; i++) {
				sum = add(sum,smallArray_[i]);
			}
			return sum / size_;
		}
	}
private:
	/**
	 * If we only need to hold a small array, it can be more efficient to
	 * store it within the object itself.
	 *
	 * Note: this is also the optimization used by `std::string`!
	 */

	//! How many elements the small array can hold

	T smallArray_[smallArraySize];

	/**
	 * A pointer to a larger array, if we need it.
	 */
	std::unique_ptr<T> largeArray_;

	//! How many elements the currently-in-use array can hold.
	size_t capacity_;

	//! How many elements are actually in the array.
	size_t size_;
};
