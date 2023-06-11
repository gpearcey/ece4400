#include <chrono>
#include <cstdlib>
#include <initializer_list>
#include <iostream>
#include <vector>
using namespace std;


#include <memory>

#include <initializer_list>

class IntegerArray
{
public:
    
    //Initializing size to be zero and values to point to null
    IntegerArray() : size_(0), values_(nullptr)
    {
    }
    
    // Constucts array and puts values in each item of the array
    IntegerArray(std::initializer_list<int> init) : size_(init.size()), values_(new int[size_])
    {
        int* ptr = values_.get();
        for (int value : init)
        {
            *ptr = value;
            ptr++;
        }
    }

    
    int* begin() const
    {
        return values_.get();
    }

    int* end() const
    {
        return values_.get() + size_;
    }

    IntegerArray& operator<<(int n)
    {
        //creating new array with increased size to add new element
        std::unique_ptr<int[]> newValues(new int[size_ + 1]);
        //copying array
        for (int i = 0; i < size_; i++)
        {
            newValues[i] = values_[i];
        }
     
        newValues[size_] = n;
        
        values_ = std::move(newValues);
        size_++;
        return *this;
    }

    size_t size() const
    {
        return size_;
    }

private:
    size_t size_;
    std::unique_ptr<int[]> values_;
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
