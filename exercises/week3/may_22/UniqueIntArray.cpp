#include <chrono>
#include <cstdlib>
#include <initializer_list>
#include <iostream>
#include <vector>
#include <memory>
using namespace std;


class IntegerArray
{
public:
	IntegerArray()
        :values_(nullptr), size_(0)
	{
	}

	IntegerArray(std::initializer_list<int> init)
		: values_(std::make_unique<int[]>(init.size()))
	{
        for (size_t i = 0; i < init.size(); i++){
            values_[i] = *(init.begin() + i);
        }
	}
    
	//return raw pointer to the start of the array
	int* begin() const
	{
	    return values_.get();
	}

	//return raw pointer to the end of the array
	int* end() const
	{
		return values_.get() + size_;
	}

	IntegerArray& operator << (int n)
	{
		//make new array one element larger
		std::unique_ptr<int[]> new_values_ = std::make_unique<int[]>(size_+1);
		//copy the elements		
        for (size_t i = 0; i < size_; i++) {
            new_values_[i] = values_[i];
        }
		//add the new number
		new_values_[size_] = n;

		//use built in move function to move the array into values_
		values_= std::move(new_values_);
		size_ = size_ + 1;

		return *this;
	}

	size_t size() const
	{
		return size_;
	}

private:
	std::unique_ptr<int[]> values_;
    size_t size_;
};

std::ostream& operator << (std::ostream&, const IntegerArray&);


// How many elements shall we store in our array?
constexpr size_t WorkingSize = 1000;


int main(int, char*[])
{
	// Create an empty IntegerArray
	IntegerArray array;

	// Initialize random number generator
	srand(static_cast<unsigned int>(time(nullptr)));

	// Add random elements to the array
	for (size_t i = 0; i < WorkingSize; i++)
	{
		unsigned long r = static_cast<unsigned long>(rand());
		array << (r % WorkingSize);
	}

	//
	// Find an arbitrary number:
	//
	bool foundIt = false;
	int index = 0;

	auto start = std::chrono::high_resolution_clock::now();
	for (int value : array)
	{
		if (value == 42)
		{
			foundIt = true;
			break;
		}

		index++;
	}
	auto end = std::chrono::high_resolution_clock::now();

	if (foundIt)
	{
		cout << "found the value 42 at index " << index;
	}
	else
	{
		cout << "42 is not in the IntegerArray array";
	}

	cout << " (took " << (end - start).count() << " µs)\n";

	//
	// Find the largest number:
	//
	start = std::chrono::high_resolution_clock::now();
	int largest = 0;
	for (auto i = array.begin(); i != array.end(); i++)
	{
		if (*i > largest)
		{
			largest = *i;
		}
	}
	end = std::chrono::high_resolution_clock::now();

	cout << "the largest value is: " << largest
	     << " (took " << (end - start).count() << " µs)\n";

	return 0;
}


std::ostream& operator << (std::ostream& o, const IntegerArray& a)
{
	o << "[";
	for (int i : a)
	{
		o << " " << i;
	}
	o << " ]\n";

	return o;
}