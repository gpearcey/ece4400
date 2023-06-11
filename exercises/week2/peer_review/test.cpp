#include<iostream>
#include<chrono>

using namespace std;

int recursive_factorial(int n){

  // if the value given to the factorial function is already 1, there is no need to continue doing the factorial so we can return the nbumber 1.
  if (n <= 1){
    return 1;
  }

  //if the number given is NOT 1 we have to continue doing the recursion as we haven't finished the factorial operation yet.
  //The number given to the recursive function is the inital given number n minus 1 as we have moved onto the NEXT part of the factorial.
  else{
    return (n * recursive_factorial(n-1));
  }

};

int iterative_factorial(int n){

  int answer = 1;
  //If a negative number is given to the function it will return 1.
  if (n <= 1){
    return 1;
  }

  else{
    for (int i = 1; i <= n; i++){
      answer *= i;
    }
    return answer;
  }
};

int main(){
  int n;
  cout << "Enter a positive integer: ";
  cin >> n;

  auto start_recursive = std::chrono::high_resolution_clock::now();
  int recursive_result = recursive_factorial(n);
  auto end_recursive = std::chrono::high_resolution_clock::now();
  cout << "The recustive difference: " << (end_recursive - start_recursive).count() << "\n";

  auto start_iterative = std::chrono::high_resolution_clock::now();
  int iterative_result = iterative_factorial(n);
  auto end_iterative = std::chrono::high_resolution_clock::now();
  cout << "The iterative difference: " << (end_iterative - start_iterative).count() << "\n";
  
}
