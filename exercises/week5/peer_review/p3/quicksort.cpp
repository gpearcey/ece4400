#include <iostream>
#include <list>
using namespace std;

template <typename T>
std::list<T> quickSort(std::list<T> &values)
{
    //end case for recurrsion.
    if (values.size() <= 1)
        return values;

    T pivot = values.back();

    std::list<T> greater;
    std::list<T> equal;
    std::list<T> less;

    //loop seperates values into respective lists
    for (T e: values)
        {
            if (e > pivot)
                greater.push_back(e);
            else if (e < pivot)
                less.push_back(e);
            else
                equal.push_back(e);
        }
    //recursive calls
    less = quickSort(less);
    greater = quickSort(greater);
    
    //splices sorted lists together after recursion
    less.splice(less.end(), equal);
    less.splice (less.end(), greater);

    return less;
}


int main()
{
    //testing
    std::list<int> values = {1,3,5,4,7,3};
    auto sorted = quickSort(values);
    for (auto element : sorted)
    {
        cout << element << endl;
    }
    return 0;
}