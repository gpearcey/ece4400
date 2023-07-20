#include "csv_graph.h"
#include <iostream>

using namespace std;

// graph implementation
int main()
{
    // graph edges array.
    Graph<string>::Edge edges[] = {
        // (x, y, w) -> edge from x to y with weight w
        {"sj","bb", 2.4},{"cb", "ca", 4.55},{"holy", "para", 6.4},{"sj", "cb", 99},{"para", "sj", 52343.3}
    };
    int N = 6;      // Number of vertices in the graph
    // calculate number of edges
    int n = sizeof(edges)/sizeof(edges[0]);
    // construct graph
    Graph<string> graph(edges, n, N);
    // print adjacency list representation of graph
    cout<<"Graph adjacency list "<<endl<<"(start_vertex, end_vertex, weight):"<<endl;
    for (int i = 0; i < N; i++)
    {
        // display adjacent vertices of vertex i
        graph.DisplayAdjList(graph.head_[i], i);
    }

    return 0;
};