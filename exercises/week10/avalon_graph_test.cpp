

#include "avalon_graph.h"

#include <iostream>
#include <ostream>
#include <string>

using namespace std;

int main()
{
	Graph<std::string, double> g;

    int v4 = g.addVertex("BB");
    int v3 = g.addVertex("CBS");
    int v5 = g.addVertex("G");
    int v6 = g.addVertex("H");
    int v2 = g.addVertex("P");
    int v1 = g.addVertex("PC");
    int v0 = g.addVertex("SJ");



    



    g.addEdge(v0,v1,14.2);
    g.addEdge(v1,v0,14.2);
    g.addEdge(v0,v2,18.6);
    g.addEdge(v2,v0,18.6);
    g.addEdge(v0,v5,14.3);
    g.addEdge(v5,v0,14.3);
    g.addEdge(v1,v3,16.4);
    g.addEdge(v3,v1,16.4);
    g.addEdge(v1,v2,12.5);
    g.addEdge(v2,v1,12.5);
    g.addEdge(v2,v5,17.5);
    g.addEdge(v5,v2,17.5);
    g.addEdge(v5,v4,15.3);
    g.addEdge(v4,v5,15.3);
    g.addEdge(v4,v6,31.9);
    g.addEdge(v6,v4,31.9);
    g.addEdge(v3,v6,24.1);
    g.addEdge(v6,v3,24.1);
    g.addEdge(v3,v2,6.6);
    g.addEdge(v2,v3,6.6);



    g.printGraph();

	return 0;
}