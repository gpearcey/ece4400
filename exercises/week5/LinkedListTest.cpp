#include "linkedList.h"
using namespace std;
int main(){
    LinkedList list;

    //for (int i = 0; i < 20; i++){
    //    list.push_back(i+0.5);
    //}

    list.push_back(1.0);
    list.push_back(2.0);

    cout << list.size() << endl;
    cout << list.front() << endl;
    cout << list.back() << endl;

    return 0;
};