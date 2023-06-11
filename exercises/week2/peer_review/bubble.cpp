#include <iostream>
#include <vector>
#include <chrono>

using namespace std;

void bubble_sort(vector<int>& array){

  int n = array.size();

  for (int i = 0; i < n - 1; i++){
    for (int j = 0; j < n - i - 1; ++j){
      if (array[j] > array[j+1]){
	int temp = array[j];
	array[j] = array[j+1];
	array[j+1] = temp;
      }
    }
  }
}

int main(){
  int n = 1;
  vector<int> arr = {};

  cout << "Enter the length you want the array to be: ";
  cin >> n;

  for (int i = 0; i < n; i++){
    arr.insert(arr.begin(),rand()%20);
  }

  cout << "Array before sorting: ";
  for (int num : arr){
    cout << num << " ";
  }

  cout << endl;

  auto start = std::chrono::high_resolution_clock::now();
  bubble_sort(arr);
  auto end = std::chrono::high_resolution_clock::now();

  cout << "Array after sorting: ";

  for (int num : arr){
    cout << num << " ";
  }

  cout << endl;

  cout << "the difference: " << (end - start).count() << "\n";

  return 0;
}
