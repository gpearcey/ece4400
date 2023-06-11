#include <iostream>
#include <vector>
#include "Expression.h"

using namespace std;

namespace calc{

//! Represents a LiteralExpression and evaluates to a double
class LiteralExpression : public Expression {
public:
    LiteralExpression(double value) : value_(value) {}

    double evaluate() const override {
        return value_;
    }

private:
    double value_;
};

//! Completes addition of two ExpPtrs
class AddOperation : public BinaryExpression {
public:
    AddOperation(ExpPtr lhs, ExpPtr rhs) : BinaryExpression(std::move(lhs),std::move(rhs)) {}

    double evaluate() const override {
        double lhsValue = lhs_->evaluate();
        double rhsValue = rhs_->evaluate();
        return lhsValue + rhsValue;
    }

    ~AddOperation() {}
};

//! Completes subtraction of two ExpPtrs
class SubtractOperation : public BinaryExpression {
public:
    SubtractOperation(ExpPtr lhs, ExpPtr rhs) : BinaryExpression(std::move(lhs),std::move(rhs)) {}

    double evaluate() const override {
        double lhsValue = lhs_->evaluate();
        double rhsValue = rhs_->evaluate();
        return lhsValue - rhsValue;
    }

    ~SubtractOperation() {}
};

//! Completes multiplication of two ExpPtrs
class MultiplyOperation : public BinaryExpression {
public:
    MultiplyOperation(ExpPtr lhs, ExpPtr rhs) : BinaryExpression(std::move(lhs),std::move(rhs)) {}

    double evaluate() const override {
        double lhsValue = lhs_->evaluate();
        double rhsValue = rhs_->evaluate();
        return lhsValue * rhsValue;
    }

    ~MultiplyOperation() {}
};

//! Completes division of two ExpPtrs
class DivideOperation : public BinaryExpression {
public:
    DivideOperation(ExpPtr lhs, ExpPtr rhs) : BinaryExpression(std::move(lhs),std::move(rhs)) {}

    double evaluate() const override {
        double lhsValue = lhs_->evaluate();
        double rhsValue = rhs_->evaluate();
        return lhsValue / rhsValue;
    }

    ~DivideOperation() {};
};

//! Creates a LiteralExpression
ExpPtr Expression::Literal(double value){
    return std::make_unique<LiteralExpression>(value);
};

//!Constructor
BinaryExpression::BinaryExpression(ExpPtr lhs, ExpPtr rhs) : lhs_(std::move(lhs)), rhs_(std::move(rhs)) {}

//! Creates a pointer to an AddOperation that can be evaluated
ExpPtr BinaryExpression::Add(ExpPtr lhs, ExpPtr rhs){
    return std::make_unique<AddOperation>(std::move(lhs),std::move(rhs));
}

//! Creates a pointer to a SubtractOperation that can be evaluated
ExpPtr BinaryExpression::Subtract(ExpPtr lhs, ExpPtr rhs){
    return std::make_unique<SubtractOperation>(std::move(lhs),std::move(rhs));
}

//! Creates a pointer to an MultiplyOperation that can be evaluated
ExpPtr BinaryExpression::Multiply(ExpPtr lhs, ExpPtr rhs){
    return std::make_unique<MultiplyOperation>(std::move(lhs),std::move(rhs));
}

//! Creates a pointer to an DivideOperation that can be evaluated
ExpPtr BinaryExpression::Divide(ExpPtr lhs, ExpPtr rhs){
    return std::make_unique<DivideOperation>(std::move(lhs),std::move(rhs));
}

ExpPtr Expression::Parse(std::string str){
    std::vector<double> numbers; //stores all numbers identified in the string
    std::vector<char> ops; //stores all operations identified in the string
    std::string number; //temporary storage for digits that make up a number
    ExpPtr value; //pointer for a BinaryExpression

    //parse string and fill vectors
    for (int i = 0; i < str.size(); i++){

        //add operations to ops vector
        if (str[i] == '+'|| str[i] == '-' || str[i] == '*' || str[i] == '/'){

            ops.push_back(str[i]);
            //let operations separate numbers, if an operation is identified, make a number from what ever digits have been collected and 
            //empty the number storage
            if (number != ""){
                numbers.push_back(std::stod(number));
                number = "";
            }            
        }
        //add digits and ',' to current number
        else if (str[i] == '.' || isdigit(str[i])){
            number.push_back(str[i]);
        }
        
        //do nothing for any other character

    }
    
    //add the last number to numbers
    if (number != ""){
        numbers.push_back(std::stod(number));
        number = "";
    }

    //Create binary expressions for each operation, from left to right
    for (int i = 0; i < ops.size(); i++) {

        if (ops[i] == '+') {
            value = BinaryExpression::Add(Literal(numbers[0]), Literal(numbers[1]));
        }
        else if (ops[i] == '-') {
            value = BinaryExpression::Subtract(Literal(numbers[0]), Literal(numbers[1]));
        }
        else if (ops[i] =='*') {
            value = BinaryExpression::Multiply(Literal(numbers[0]), Literal(numbers[1]));
        }
        else if (ops[i] == '/') {
            value = BinaryExpression::Divide(Literal(numbers[0]), Literal(numbers[1]));
        }

        //remove the two numbers just processed
        numbers.erase(numbers.begin());
        numbers.erase(numbers.begin());
        //add the result of the most recent operation to the front of the array
        numbers.insert(numbers.begin(), value->evaluate());

    }
    ExpPtr result = Literal(numbers.front());


    return result;
}

}//namespace calc



