#include "tree.h"

template<typename T>
void visit(const T &value)
{
	static size_t i = 0;
	std::cout << "Node " << i++ << ": " << value << "\n";
}


int main() {
    Tree<int> t;
    t.setRoot(2);
    t.addChild(4);
    t.addChild(5);

    Tree<int> t2;
    t2.setRoot(3);
    t2.addChild(6);
    t2.addChild(7);

    Tree<int> t3;
    t3.setRoot(1);
    t.addSubtree(std::move(t));
    t.addSubtree(std::move(t2));


    t3.visitPreorder(visit<int>);
    t3.visitPostorder(visit<int>);



    return 0;
}