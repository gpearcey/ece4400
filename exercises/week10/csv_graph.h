
#include <cstddef>   
#include <iostream>

using namespace std;
template<typename T>
class Graph
{
public:

	struct Vertex; 
    struct Edge;
    Vertex* addVertex(T value, float weight, string head)   
    {
        Vertex* new_vertex = new Vertex;
        new_vertex->town_ = value;
        new_vertex->dist_fr_prev_vertex_ = weight;
         
        new_vertex->next_ = head;   
        return new_vertex;
    };

    Graph(Edge edges[], size_t num_edges, size_t num_vertexes){
        head_ = new Vertex*[num_vertexes];
        this->num_vertexes_ = num_vertexes;
        for (int i = 0; i < num_vertexes; ++i){
            head_[i] = nullptr;
        }
        for (unsigned i = 0; i < num_edges; i++)  
        {
            T start_vertex = edges[i].start_vertex;
            T end_ver = edges[i].end_vertex;
            double weight = edges[i].distance;
            Vertex* new_vertex = addVertex(end_ver, weight, head_[start_vertex]);
            head_[start_vertex] = new_vertex;
        }
    }


    ~Graph() {
        for (int i = 0; i < num_vertexes_; i++)
        {
            delete[] head_[i];
        }
            delete[] head_;
     }

    void DisplayAdjList(Vertex* ptr, int i)
    {
        while (ptr != nullptr) {
            cout << "(" << i << ", " << ptr->town_
                << ", " << ptr->dist_fr_prev_vertex_ << ") ";
            ptr = ptr->next_;
        }
        cout << endl;
    }

    struct Vertex
    {
        T town_;
        double dist_fr_prev_vertex_;
        Vertex* next_;
    };

    struct Edge
    {
        T start_vertex;
        T end_vertex;
        double distance;
    };
    
	Vertex** head_;
private:
    
    size_t num_vertexes_;



};

