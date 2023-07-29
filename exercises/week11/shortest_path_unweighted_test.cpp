#include "shortest_path_unweighted.h"
#include <iostream>

using namespace std;

// graph implementation
int main()
{
    Graph<int,int> g;

    g.addVertex(0);
    g.addVertex(1);
    g.addVertex(2);
    g.addVertex(3);

    g.addEdge(0,1);
    g.addEdge(1,2);
    g.addEdge(2,3);
    g.addEdge(3,0);

    for (int i = 0; i < g.neighbors_.size(); i++)
    {

        cout << "source: " << i << endl;
        for (auto j: g.neighbors_[i]) {
            cout << j.getValue() << endl;
        }
        
    }


    std::vector<int> dist = g.shortestNaive(0);
    std::vector<int> dist_WL = g.shortestWorkList(0);

    for (auto i : dist)
    {
        cout << i;
    }
    cout << endl;

    for (auto i : dist_WL)
    {
        cout << i;
    }
    cout << endl;

    g.printDistanceMatrix();
    return 0;
};