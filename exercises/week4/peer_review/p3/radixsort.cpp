#include <iostream>
#include <algorithm>
#include <vector>
#include <string>

using namespace std;

template<typename T>
void radixSort(vector<T>& arr) {           
    T max_val = *max_element(arr.begin(), arr.end());      // We find the max value here using max_element from algorithm library
    
    for(int exp = 1; max_val/exp > 0; exp *= 10)
    {
        vector<T> temp(arr.size());                  //New vector to store sorted elements
        int count[10] = {0};

        for(auto& num : arr)
            count[(num/exp)%10]++;

        for(int i = 1; i < 10; i++)
            count[i] += count[i - 1];

        for(int i = arr.size() - 1; i >= 0; i--)
        {
            temp[count[(arr[i]/exp)%10] - 1] = arr[i];
            count[(arr[i]/exp)%10]--;
        }
 
        arr = temp;
    }
}

template<>
void radixSort<string>(vector<string>& arr) {
    size_t max_length = 0;
    for(auto& str : arr)
        max_length = max(max_length, str.size());
    
    for(int pos = max_length - 1; pos >= 0; pos--)
    {
        vector<string> temp(arr.size());
        int count[256] = {0};                       // Array size of 256 to cover all ASCII chars

        for(auto& str : arr)
            count[(pos < str.size() ? str[pos] : 0)]++;

        for(int i = 1; i < 256; i++)
            count[i] += count[i - 1];

        for(int i = arr.size() - 1; i >= 0; i--)
        {
            temp[count[(arr[i].size() > pos ? arr[i][pos] : 0)] - 1] = arr[i];
            count[(arr[i].size() > pos ? arr[i][pos] : 0)]--;
        }

        arr = temp;
    }
}

int main() {
    //Integer sort test
    vector<int> numbers = {50, 24, 700, 2, 35};
    radixSort(numbers);
    cout << "Sorted numbers: ";
    for (auto num : numbers) {
        cout << num << " ";
    }
    cout << endl;


    //String sort test
    vector<string> strings = {"sup", "zebra", "based", "redpilled", "sigma", "male"};
    radixSort(strings);
    std::cout << "Sorted strings: ";
    for (auto &str : strings) {
        cout << str << " ";
    }
}