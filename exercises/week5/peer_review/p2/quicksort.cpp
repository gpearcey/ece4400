#include <iostream>
#include <memory>
#include <list>

template <typename T>
std::list<T> quicksort(std::list<T> input)
{

    if (input.size() <= 1)
    {
        return input;
    }

    T pivot = *std::next(input.begin(), input.size() / 2);

    std::list<T> less;
    std::list<T> greater;
    std::list<T> equal;

    for (const T &element : input)
    {
        if (element < pivot)
        {
            less.push_back(element);
        }
        else if (element > pivot)
        {
            greater.push_back(element);
        }
        else
        {
            equal.push_back(element);
        }
    }

    less = quicksort(std::move(less));
    greater = quicksort(std::move(greater));

    less.splice(less.end(), equal);
    less.splice(less.end(), greater);

    for (const int &element : less)
    {
        std::cout << element << " ";
    }
    std::cout << std::endl;

    return less;
}

int main()
{

    std::list<int> input = {89, 674, 33, 51, 95, 1000, 397};
    std::list<int> output = quicksort(input);

    for (const int &element : output)
    {
        std::cout << element << " ";
    }

    std::cout << std::endl;

    return 0;
}