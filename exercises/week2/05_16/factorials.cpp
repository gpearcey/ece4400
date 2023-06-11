#include <iostream>
#include <chrono>

int recursiveFactorial (int n) {
    if (n==1) {
        return 1;
    }
    int factorial = n * recursiveFactorial(n-1);
    return factorial;
}

int iterativeFactorial (int n) {
    int factorial = 1;
    while (n>1) {
        factorial = factorial * n;
        n = n -1;
    }
    return factorial;
}

int main() {
    //user input
    int n;
    std::cout << "get factorial for: ";
    std::cin >> n;
    
    //iterative approach
    auto start = std::chrono::high_resolution_clock::now();
    std::cout << iterativeFactorial(n) << std::endl;
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    std::cout << "Iterative Execution time: " << duration << " ms" << std::endl;
    
    //recursive approach
    start = std::chrono::high_resolution_clock::now();
    std::cout << recursiveFactorial(n) << std::endl;
    end = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    std::cout << "Recursive Execution time: " << duration << " ms" << std::endl;
    
    return 0;
}