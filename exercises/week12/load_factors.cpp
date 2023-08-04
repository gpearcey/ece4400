#include "string_hash.h"
#include <unordered_set>
#include <chrono>
/**
 * Write a program that inserts 10,000 integers (0 through 9,999) into a std::unordered_set<int>. 
 * Let this program set the maximum load factor for the set (using unordered_set<T>::max_load_factor()) according to a value passed at the command line.

Plot the average time that your program takes to insert 10,000 elements against load factor. 
If you’re running on Windows and the Windows timing trick doesn’t work on your platform, you may time the complete execution time for your program 
rather than isolating just the insertion with std::chrono. Why did you choose the load factor values that you did?
*/
using namespace std;
using namespace std::chrono;
int main()
{

    std::unordered_set<int> s;

    //// Setting Max Load Factor via user input
    float load_factor;
    cout << "Enter a max load factor: ";
    cin >> load_factor;
    cout << endl;
    s.max_load_factor(load_factor);
    auto start = high_resolution_clock::now();
    for (int i = 0; i < 10000; i++)
    {
        s.insert(i);
    } 
    auto end = high_resolution_clock::now();
    duration<double, milli> time = end - start;
    cout << load_factor << "," << time.count() << endl; 

    //for (float j=1; j<10; j++)
    //{
    //    
    //    s.max_load_factor(j/10.0);
//
    //    auto start = high_resolution_clock::now();
    //    for (int i = 0; i < 10000; i++)
    //    {
    //        s.insert(i);
    //    } 
    //    auto end = high_resolution_clock::now();
    //    duration<double, milli> time = end - start;
//
    //    cout << (j/10) << "," << time.count() << endl; 
    //}

    return 0;
}