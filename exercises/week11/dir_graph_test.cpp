#include "directed_graph.h"
#include <iostream>
#include <string>

using namespace std;

int main()
{
    /**
     * Weighted, Directed Graph
    */
    Graph<string,float> g;

    int BB = g.addVertex("BB");
    int CBS = g.addVertex("CBS");
    int G = g.addVertex("G");
    int H = g.addVertex("H");
    int P = g.addVertex("P");
    int PC = g.addVertex("PC");
    int SJ = g.addVertex("SJ");

    g.addEdge(PC,SJ,14.2);
    g.addEdge(P,SJ,18.6);
    g.addEdge(G,SJ,14.3);
    g.addEdge(CBS,PC,16.4);
    g.addEdge(P,PC,12.5);
    g.addEdge(P,G,17.5);
    g.addEdge(BB,G,15.3);
    g.addEdge(H,BB,31.9);
    g.addEdge(H,CBS,24.1);
    g.addEdge(CBS,P,6.6);


    //std::vector<float> d = g.shortestDijkstras(H, );
//
    //for (auto i : d)
    //{
    //    cout << i;
    //}
    //cout << endl;
    //g.printDistanceMatrixWeighted();

    //g.topoSort();
    g.dfs(0);

    return 0;
};