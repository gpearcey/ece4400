

#include "adj_matrix.h"

#include <iostream>
#include <ostream>
using namespace std;

int main()
{
	Graph<int, int> g;

    int v0 = g.addVertex(6);
    int v1 = g.addVertex(0);
    int v2 = g.addVertex(0);
    int v3 = g.addVertex(0);
    int v4 = g.addVertex(0);

    

    g.addEdge(v0,v0,1);
    g.addEdge(v1,v0,1);
    g.addEdge(v3,v4,1);
    g.addEdge(v2,v0,1);

    g.printGraph();

	return 0;
}