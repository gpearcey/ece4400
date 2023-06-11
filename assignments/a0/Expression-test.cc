#include <iostream>
#include "Expression.h"

int main() {
    // Test code goes here
    calc::ExpPtr expression = calc::Expression::Parse("0.5");
    double result = expression->evaluate();
    std::cout << "Result: " << result << std::endl;
    
    return 0;
}