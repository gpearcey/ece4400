#include "sibling_tree.h"

int main() {
    Tree<int> t;
    t.setRoot(1);
    t.addChild(2);
    t.addChild(3);

    Tree<int> t2;
    t2.setRoot(4);
    t2.addChild(5);
    t.addSubtree(std::move(t2));


    t.printTree(); //prints out 1,2,3,4,5


    return 0;
}