#include "tree.h"

int main() {
    Tree<int> t;
    t.setRoot(5);
    t.addChild(2);
    t.addChild(8);

    //t.printTree();

    return 0;
}