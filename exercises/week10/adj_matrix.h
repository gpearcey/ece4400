/**
 * Adjacency matrix
 * 
 * @todo add comments
*/
#include <iostream>
#include <vector>

using namespace std;

template<typename V, typename E>
class Graph
{
private:
	struct Vertex; //Forward declaration

public:
	
	using VertexID = size_t;

	Graph()
		: num_verticies_(0)
	{}

	VertexID addVertex(V &&value){

		Vertex v(std::move(value), num_verticies_);
		verticies_list_.push_back(v);

		updateMatrix();
		return num_verticies_++;

	};

	void addEdge(VertexID i, VertexID j, E edge){
		adj_matrix_[i][j] = edge;
		return;
	};

	void printGraph(){
		for (auto& i : adj_matrix_){
			for (auto j : i){
				std::cout << j;
			}
			std :: cout << "\n";
		}
		return;
	}

private:
	size_t num_verticies_;
	std::vector<std::vector<E>> adj_matrix_; 
	std::vector<Vertex> verticies_list_;

	struct Vertex
	{

		Vertex(V &&value, VertexID id)
			: element_(std::move(value)), id_(id)
		{
		}

		const V& value() const { return element_; }

		V element_;
		size_t id_;
	};

	void updateMatrix(){
		if (adj_matrix_.empty()){
			adj_matrix_.push_back({E()});
			return;
		}

		for (auto& row : adj_matrix_) {
        	row.push_back(E());
    	}
		std::vector<E> new_row((num_verticies_+1), E());
		adj_matrix_.push_back(new_row);

		return;
	}
};