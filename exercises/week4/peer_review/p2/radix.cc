#include <iostream>
#include <vector>
#include <string>
#include "radix.h"

int main()
{
    std::vector<std::string> arr = { "apple", "banana", "cherry", "date", "elderberry" };
    radixSort(arr);

    std::cout << "Sorted array: ";
    for (const auto& str : arr)
        std::cout << str << " ";
    std::cout << std::endl;

    return 0;
}