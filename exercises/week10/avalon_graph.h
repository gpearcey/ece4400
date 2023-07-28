/**
 * Adjacency matrix
 * 
 * @todo add comments
*/
#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

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
				std::cout << j << " ";
			}
			std :: cout << "\n";
		}
		return;
	}

	E getDistance(VertexID start, VertexID end){
	// Set up table of distances and paths

	for (Vertex v : verticies_list_){
		v.dist_ = 0;
		v.done_ = false;
	}

	// The distance from the start vertex to itself is 0
	start.dist_ = 0;

	while (verticiesNotDone())
	{
		Vertex v = verticies_list_[smallestDistance()];

		for (int i; i = 0; i<adj_matrix_.size()){
			Vertex n = verticies_list_(i);
			if (!n.done_){
				// How long is the path through v to this neighbour?
				distance = v.dist_ + adj_matrix_[v.id_][i];
			}
		}
	}

	bool verticiesNotDone(){
		for (Vertex v : verticies_list_)
		{
			if (v.done_ == false){
				return true;
			}
		}
		return false;
	}

	VertexID smallestDistance(){
		E smallest_dist = verticies_list[0].dist_;
		VertexID id = verticies_list[0].id_;
		for (Vertex v : verticies_list_)
		{
			if(v.dist_ < smallest_dist)
			{
				smallest_dist = v.dist_;
				id = v.id_;
			}
		}
		return id;
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
		size_t path_;
		E dist_;
		bool done_;
	};

	void updateMatrix(){
		if (adj_matrix_.empty()){
			adj_matrix_.push_back({E()});
			return;
		}

		for (auto& row : adj_matrix_) {
        	row.push_back(E());
    	}
		std::vector<E> new_row((num_verticies_+1), -1);
		adj_matrix_.push_back(new_row);

		return;
	}
};