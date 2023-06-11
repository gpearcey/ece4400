#include <iostream>
using namespace std;

void factorial(int x)
{
    int value = 1;

    if (x!=1){
        for (int i=1; i <= x){
            value *= x ; 
            int i++;
            factorial(int x - 1)
    }
    else{
        return (1);
    }
    }
    cout << value << endl;
}

int main() {

   factorial(4);
    
    return 0;
}

void 2_factorial(){
    int value_2 = 1;
    for (int i=0; i < x; i++){
        value_2 *= i + 1 ; 
    cout << value_2<< endl;
}

