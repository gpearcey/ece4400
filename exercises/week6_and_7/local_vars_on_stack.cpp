#include <iostream>

using namespace std;

void nested_function()
{
    int d;
    int e;
    int f;
    //memory addresses should be smaller than that of a, b, and c
    cout << "Nested Function - Memory address of d: " << &d << endl;
    cout << "Nested Function - Memory address of e: " << &e << endl;
    cout << "Nested Function - Memory address of f: " << &f << endl;
}

void function(){
    int a;
    int b;
    int c;
    cout << "Function - Memory address of a: " << &a << endl;
    cout << "Function - Memory address of b: " << &b << endl;
    cout << "Function - Memory address of c: " << &c << endl;

    //variables placed on the stack in nested_function will be placed below a, b and c, showing the stack grows downwards.
    nested_function(); 

}

int main(){
    function();

    return 0;
}