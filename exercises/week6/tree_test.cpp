#include "tree.h"

int main() {
    Tree<int> t;
    t.setRoot(1);
    t.addChild(2);
    t.addChild(3);

    //t.printTree();

    Tree<int> t2;
    t2.setRoot(4);
    t2.addChild(5);
    t.addSubtree(std::move(t2));

    //t.printTree();

    t.addChild(6);

    Tree<int> t3;
    t3.setRoot(7);
    t3.addChild(8);

    Tree<int> t4;
    t4.setRoot(9);
    t4.addChild(10);

    t3.addSubtree(std::move(t4));
    t.addSubtree(std::move(t3));

    t.printTree();

    return 0;
}