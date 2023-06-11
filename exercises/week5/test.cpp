#include <list>
#include <iostream>
#include "quickSort.h"


int main()
{
    std::list<int> l = {2,1,3,4,2,5,7,3,6,5,4,4,4};
    quickSort(l);

    std::cout << "l = { ";
    for (int n : l)
        std::cout << n << ", ";
    std::cout << "};\n";

    return 0;
}
