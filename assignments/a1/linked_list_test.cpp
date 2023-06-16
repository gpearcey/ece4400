#include "List.h"

using namespace std;

int main(){
    List<int> l;

    //check if list is empty
    cout << l.empty() << endl;

    //copy an element to the front of the list
    int i = 6;
    l.push_front(i);
    l.push_front(85);
    l.push_back(i);
    l.push_back(i);


    //check if list is empty
    cout << l.empty() << endl;
    

    //move an element to the front of the list
    List<std::unique_ptr<int>> b;
    std::unique_ptr<int> u_ptr0 = std::make_unique<int>();
    std::unique_ptr<int> u_ptr1 = std::make_unique<int>();
    
    b.push_front(std::move(u_ptr0));
    b.push_front(std::move(u_ptr1));

    //move an element to the back of the list
    std::unique_ptr<int> u_ptr2 = std::make_unique<int>();
    b.push_back(std::move(u_ptr2));

    //testing copy constructor
    //List<int> list;
    //List<int> copy_list = list;

    //testing copy constructor
    List<double> c;
    c.push_back(45.6);
    List<double> d = c;

    //testing copy assignment operator
    List<double> e = d;

    cout << e.empty() << endl;

    e = std::move(d);
    
    //cout << d.empty() << endl; would cause a segmentation fault because we've moved it!
    
    auto iter = e.begin();

    cout << *iter << endl;

    e.push_back(76.544);

    ++iter;


    cout << *iter << endl;
    e.push_back(84);

    iter++;

    cout << *iter << endl;

    auto iter1 = e.begin();
    iter1++;
    //iter1++;

    if (iter == iter1){
        cout << "iterators are equal" << endl;
    }

    if (iter != iter1){
        cout << "iterators are not equal" << endl;
    }

    e.insert(iter1, 52);

    e.erase(iter1);
    return 0;
};