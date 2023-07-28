
#include <cstddef>   
#include <iostream>
#include <vector>

using namespace std;
template<typename T>
class Graph
{
public:

    template<typename V>
	struct Vertex
	{

		Vertex(V &&value, size_t id)
			: element_(std::move(value)), id_(id)
		{
		}

		const V& getValue() const { return element_; }
        const V& getID() const { return id_; }

		V element_;
		size_t id_;
	};


    void addVertex(T value)   
    {
        Vertex* new_vertex = new Vertex(value, this->verticies_.size());
        verticies.push_back(new_vertex);
        return;
    };

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
        T end_vertex;
        double distance;
    };
    
	std::vector<Vertex> verticies_;
    std::vector<int> distance_;
    std::vector<std::vector<Vertex>> neighbors_;
    std::vector<Vector> path_;

private:
    
    size_t num_vertexes_;



};
