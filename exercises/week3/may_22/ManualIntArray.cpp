#include <chrono>
#include <cstdlib>
#include <initializer_list>
#include <iostream>
#include <vector>
using namespace std;


class IntegerArray
{
public:
	IntegerArray()
        :values_(nullptr), size_(0)
	{
	}

	IntegerArray(std::initializer_list<int> init)
		: values_(new int[init.size()])
	{
        size_t i = 0;
        for (i < init.size(); i++;){
            values_[i] = *(init.begin() + i); //fill in array values from initialized list
        }
	}
    
    IntegerArray(const IntegerArray& other) 
        : size_(other.size_) 
    {
        values_ = new int[size_];
        for (size_t i = 0; i < size_; i++) {
            values_[i] = other.values_[i];
        }
    }

	IntegerArray(IntegerArray&& other)
		: values_(other.values_), size_(other.size_)
	{
		//set the other pointer to null because it is getting moved
        other.values_ = nullptr;
        other.size_ = 0;
	}

	int* begin() const
	//return a pointer to the beginning of the array
	{
		return values_;
	}

	int* end() const
	//return a pointer to the end of the array
	{
		return values_ + size_;
	}

	IntegerArray& operator << (int n)
	{
		//make new array that's one element bigger than current one
		int* new_values_ = new int[size_+1];
		//copy the elements		
        for (size_t i = 0; i < size_; i++) {
            new_values_[i] = values_[i];
        }
		//add the new number
		new_values_[size_] = n;
		//delete the old array and set values_ to new array
		delete[] values_;
		values_ = new_values_;
		//increase the array size
		size_ = size_ + 1;

		return *this;
	}

	size_t size() const
	{
		return size_;
	}

    ~IntegerArray()
    {
        delete[] values_;
    }

private:
	int* values_;
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