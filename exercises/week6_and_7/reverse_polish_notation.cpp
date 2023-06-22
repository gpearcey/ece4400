#include <iostream>
#include <string>
#include <sstream>
#include <stack>
#include <vector>

/**
 * isInt
 * returns true if string can sucessfully be converted into an integer, and updates number variable to the converted string
 * returns false if not an integer
 * The reverse Polish notation (RPN) is a notation for expressing mathematical operations without requiring parentheses. '
 * Unlike infix notation (e.g., 1+2), calculations can be done in a single pass through the token stream — no additional parsing is required.
 *  Write a function that accepts a pair of iterators over a container of strings (e.g., { "1", "2", "+", "3", "*" }) 
 * and that returns an integer derived from an RPN interpretation of the strings (in the example above, 9).
*/
bool isInt(std::string value, int& number){
    std::stringstream ss(value);
    if (ss >> number){
        return true;
    } 
    else{
        return false;
    }
}

/**
 * isOperator
 * returns true if op is a supported operator, false if not
*/
bool isOperator(std::string op){
    if (op == "+" || op == "-" || op == "*" || op == "/"){
        return true;
    } 
    else{
        return false;
    }
}

/**
 * parseRPN
 * iterates over an object containing strings forming an expression in reverse polish notation
 * returns the result of the expression
*/
template<typename Iter>
int parseRPN(const Iter& begin, const Iter& end){
    std::stack<int> stck;    

    int number;
    for (auto i = begin; i < end; i++){

        //check if string is an integer
        if (isInt(*i,number)){
            stck.push(number);//add to stack if it's a number
            std::cout << "Pushed " << number << " onto stack \n";
        }
        //check if string is a operator
        else if (isOperator(*i)){
            //push top 2 numbers from stack to operate on
            int number1 = stck.top();
            stck.pop();
            int number0 = stck.top();
            stck.pop();
            int result;

            //perform operation
            if (*i == "+"){
                result = number0 + number1;
            }
            else if (*i == "-"){
                result = number0 - number1;
            }
            else if (*i == "*"){
                result = number0 * number1;
            }
            else if (*i == "/"){
                result = number0 / number1;
            }
            else {
                std::cout << "error: not a supported operator" << std::endl;
            }
            //push result back onto stack
            stck.push(result);
        }
        else{
            std::cout << "error: invalid string" << std::endl;
        }
    }

    //return final result after entire object is parsed
    int final_result = stck.top();
    return final_result;
};


int main(){

    
    std::vector<std::string> rpn_expression = { "3", "4", "*", "5", "6", "*","+" }; //equivalent to (3*4) + (5*6) 

    int result = parseRPN(rpn_expression.begin(),rpn_expression.end());

    std::cout << result << std::endl;

    return 0;
};

