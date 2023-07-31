#include "unweighted_graph.h"
#include <iostream>

using namespace std;

int main()
{
    /**
     * Unweighted Graph
    */
    Graph<int,int> g;

    g.addVertex(0);
    g.addVertex(1);
    g.addVertex(2);
    g.addVertex(3);

    g.addEdge(0,1);
    g.addEdge(1,2);
    g.addEdge(2,3);
    g.addEdge(3,0);


    std::vector<int> dist = g.shortestNaive(0);
    std::vector<int> dist_WL = g.shortestWorkList(0);

    //for (auto i : dist)
    //{
    //    cout << i;
    //}
    //cout << endl;
//
    //for (auto i : dist_WL)
    //{
    //    cout << i;
    //}
    //cout << endl;
//
    //g.printDistanceMatrix();

        /**
     * Unweighted Graph
    */
    Graph<int,int> wg;

    wg.addVertex(0);
    wg.addVertex(1);
    wg.addVertex(2);
    wg.addVertex(3);
    wg.addVertex(4);
    wg.addVertex(5);

    wg.addEdge(0,1,5);
    wg.addEdge(0,2,2);
    wg.addEdge(1,3,3);
    wg.addEdge(2,3,1);
    wg.addEdge(2,4,1);
    wg.addEdge(3,5,2);
    wg.addEdge(4,5,4);

    std::vector<int> d = wg.shortestDijkstras(0);

    //for (auto i : d)
    //{
    //    cout << i;
    //}
    //cout << endl;

    //wg.printDistanceMatrixWeighted();

    return 0;
};