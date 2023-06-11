#include <iostream>
#include <chrono>

using namespace std;

template <typename T, size_t size>
void bubbleSort (T (&arr)[size]) { 
  
  for (int j=0; j<size-1;j++) {
    for (int i=0; i<size-1; i++) {
        if (arr[i] > arr[i+1]){
            T temp = arr[i];
            arr[i] = arr[i+1];
            arr[i+1] = temp;
        }
    }
  }
  return;
}
template <typename T, size_t size>
void printArray(T (&arr)[size]) {
    for(int i=0; i<size; i++){
        cout << arr[i] << endl;
    }
}

template <typename T, size_t size>
void genArr (T (&arr)[size]){
  for (int i = 0; i<size;i++){
    arr[i] = rand() % 10000;  
  }
  return;
}
    
int main () {

  //initialize arrays
  int a[5];
  int b[10];
  int c[50];
  int d[100];
  int e[1000];
  int f[10000];
  int g[100000];
  int h[1000000];
  int i[500000];
  int j[50000];
  int k[5000];
  int l[500];

  //fill arrays with random numbers
  genArr(a);
  genArr(b);
  genArr(c);
  genArr(d);
  genArr(e);
  genArr(f);
  genArr(g);
  genArr(h);
  genArr(i);
  genArr(j);
  genArr(k);
  genArr(l);

  //sort arrays and print the time taken to sort, print the smaller arrays
  auto start = std::chrono::high_resolution_clock::now();
  bubbleSort(a);
  auto end = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
  std::cout << "Sorting a time: " << duration << " ms" << std::endl;
  printArray(a);

  start = std::chrono::high_resolution_clock::now();
  bubbleSort(b);
  end = std::chrono::high_resolution_clock::now();
  duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
  std::cout << "Sorting b time: " << duration << " ms" << std::endl;
  printArray(b);

  start = std::chrono::high_resolution_clock::now();
  bubbleSort(c);
  end = std::chrono::high_resolution_clock::now();
  duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
  std::cout << "Sorting c time: " << duration << " ms" << std::endl;
  printArray(c);

  start = std::chrono::high_resolution_clock::now();
  bubbleSort(d);
  end = std::chrono::high_resolution_clock::now();
  duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
  std::cout << "Sorting d time: " << duration << " ms" << std::endl;
  printArray(d);

  start = std::chrono::high_resolution_clock::now();
  bubbleSort(e);
  end = std::chrono::high_resolution_clock::now();
  duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
  std::cout << "Sorting e time: " << duration << " ms" << std::endl;

  start = std::chrono::high_resolution_clock::now();
  bubbleSort(f);
  end = std::chrono::high_resolution_clock::now();
  duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
  std::cout << "Sorting f time: " << duration << " ms" << std::endl;

  start = std::chrono::high_resolution_clock::now();
  bubbleSort(g);
  end = std::chrono::high_resolution_clock::now();
  duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
  std::cout << "Sorting g time: " << duration << " ms" << std::endl;

  start = std::chrono::high_resolution_clock::now();
  bubbleSort(h);
  end = std::chrono::high_resolution_clock::now();
  duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
  std::cout << "Sorting h time: " << duration << " ms" << std::endl;

  start = std::chrono::high_resolution_clock::now();
  bubbleSort(i);
  end = std::chrono::high_resolution_clock::now();
  duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
  std::cout << "Sorting i time: " << duration << " ms" << std::endl;

  start = std::chrono::high_resolution_clock::now();
  bubbleSort(j);
  end = std::chrono::high_resolution_clock::now();
  duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
  std::cout << "Sorting j time: " << duration << " ms" << std::endl;

  start = std::chrono::high_resolution_clock::now();
  bubbleSort(k);
  end = std::chrono::high_resolution_clock::now();
  duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
  std::cout << "Sorting k time: " << duration << " ms" << std::endl;

  start = std::chrono::high_resolution_clock::now();
  bubbleSort(l);
  end = std::chrono::high_resolution_clock::now();
  duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
  std::cout << "Sorting l time: " << duration << " ms" << std::endl;

  

  return 0;
}
