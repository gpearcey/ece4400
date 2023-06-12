#include <iostream>
#include <list>
using namespace std;

template <typename T>
void quickSort (list<T> &unsortedList)
{
    //Check if list is broken into a single element
    if (unsortedList.size() <= 1)
    {
        return;
    }
    //Creating smaller lists to split our list into
    list<T> lesser;
    list<T> equal;
    list<T> greater;
    
    //Making last element the pivot
    T pivot = unsortedList.back();
    
    //Fill the smaller lists from the given list
    for (T &element: unsortedList)
    {
        if (element < pivot)
        {
            lesser.push_back(element);
        }
        else if (element == pivot)
        {
            equal.push_back(element);
        }
        else if (element > pivot)
        {
            greater.push_back(element);
        }
    }
    
    //Recursively sort the smaller lists
    quickSort(lesser);
    quickSort(greater);
    
    unsortedList.clear();
    
    unsortedList.splice(unsortedList.end(), lesser);
    unsortedList.splice(unsortedList.end(), equal);
    unsortedList.splice(unsortedList.end(), greater);
};

int main()
{
    list<double> doubleList = {174.1, 46.4, 3.14, 5.4, 5.2, 6.9, 11.4, 312.5};
    cout << "Before sorting, the list is: ";
    for (double element: doubleList)
    {
        cout << element << " ";
    }
    
    quickSort(doubleList);
    
    cout << endl;
    cout << "After sorting, the list is: ";
    for (double element: doubleList)
    {
        cout << element << " ";
    }
    
    return 0;
}
