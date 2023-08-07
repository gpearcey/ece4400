
#include <cstddef>   
#include <iostream>
#include <vector>
#include <queue>
#include <cmath>

using namespace std;
template<typename T, typename E>
/*
* Undirected Graph

https://www.interviewcake.com/concept/java/topological-sort
*/
class Graph
{
public:

    Graph(){}


    template<typename V>
	struct Vertex
	{

		Vertex(V &&value, size_t id)
			: element_(std::move(value)), id_(id)
		{
		}

		const V& getValue() const { return element_; }
        const size_t& getID() const { return id_; }

		V element_;
		size_t id_;
        E distance_;
	};

	std::vector<Vertex<T>> verticies_;
    std::vector<E> distance_;
    std::vector<std::vector<Vertex<T>>> neighbors_;
    std::vector<Vertex<T>> path_;


    size_t addVertex(T value)   
    {
        Vertex<T> new_vertex(std::forward<T>(value), this->verticies_.size());
        verticies_.push_back(new_vertex);
        neighbors_.resize(verticies_.size());
        return new_vertex.getID();
    };

    void addEdge(size_t v1, size_t v2, E distance)
    {
        Vertex<T> v1_copy = verticies_[v1];
        v1_copy.distance_ = distance;
        Vertex<T> v2_copy = verticies_[v2];
        v2_copy.distance_ = distance;
        neighbors_[v1].push_back(v2_copy);
        neighbors_[v2].push_back(v1_copy);
        return;
    }

    void addEdge(size_t v1, size_t v2)
    {
        Vertex<T> v1_copy = verticies_[v1];
        v1_copy.distance_ = 1;
        Vertex<T> v2_copy = verticies_[v2];
        v2_copy.distance_ = 1;
        neighbors_[v1].push_back(v2_copy);
        neighbors_[v2].push_back(v1_copy);
        return;
    }

    std::vector<E> shortestNaive(size_t source)
    {
        std::vector<E> distance(verticies_.size(), -1);
        std::vector<size_t> path(verticies_.size(), 0);
        std::vector<bool> done(verticies_.size(), false);
        distance[source] = 0;

        for (size_t dist = 0; dist < verticies_.size(); ++dist)
        {   
            for(auto v : verticies_)
            {
                if (done[v.getID()] || distance[v.getID()] != dist)
                {   
                    continue;
                }

                for (auto n: neighbors_[v.getID()])
                {   
                    
                    if(distance[n.getID()] == -1)
                    {
                        distance[n.getID()] = dist + 1;
                        path[n.getID()] = v.getID();
                    }
                }
                done[v.getID()] = true;

            }
        }

        return distance;
    }

    std::vector<E> shortestWorkList(size_t source)
    {
        std::vector<E> distance(verticies_.size(), -1);
        std::vector<size_t> path(verticies_.size(), 0);
        std::vector<bool> done(verticies_.size(), false);
        distance[source] = 0;

        std::queue<size_t> q;

        q.push(source);

        while (!q.empty()){
            size_t v = q.front();
            q.pop();

            for (auto n: neighbors_[v])
            {                   
                if(distance[n.getID()] == -1)
                {
                    distance[n.getID()] = distance[v] + 1;
                    path[n.getID()] = v;
                    q.push(n.getID());
                }
            }
        }

        return distance;
    }

    bool verticiesDone(std::vector<bool> &vec)
    {
        for (auto i : vec) {
            if (i == false)
            {
                return false;
            }

        }

        return true;
    }
    std::vector<E> shortestDijkstras(size_t source)
    {
        std::vector<E> distance(verticies_.size(), INFINITY);
        std::vector<size_t> path(verticies_.size(), 0);
        std::vector<bool> done(verticies_.size(), false);
        distance[source] = 0;
        Vertex<E> v = verticies_[0];
        while (!verticiesDone(done))
        {
            //cout << "verticies not done" << endl;
            
            for (auto i : this->verticies_)
            {
                //cout << "checking if i is smaller" << endl;
                if ((distance[i.getID()] < distance[v.getID()]) && (done[i.getID()] == false))
                {
                    v = i;
                    cout << "updating v" << endl;
                }
            }

            //cout << "element value: " << v.getValue() << endl;
            // TODO set all n.done to false, then set true
            for (auto n : neighbors_[v.getID()])
            {
                E weight = n.distance_;
                cout << "weight " << weight << endl;

                if (!done[n.getID()])
                {
                    E dist = distance[v.getID()] + n.distance_;
                    cout << "dist " << dist << endl;
                    if (distance[n.getID()] > dist)
                    {
                        distance[n.getID()] = dist;
                        path[n.getID()] = v.getID();
                    }
                }

            }

            //cout << " done status of v: " <<  done[v.getID()] << endl;

            done[v.getID()] = true;

            
        }
        return distance;
    }

    void printDistanceMatrix() {
        std::vector<std::vector<E>> matrix;
        
        // Create Matrix
        for (int i = 0; i < verticies_.size(); i++)
        {
            matrix.push_back(shortestWorkList(i));
        }

        // Print Matrix        
        for (int j = 0; j < verticies_.size(); j++)
        {
            for (int k = 0; k < verticies_.size(); k++)
            {
                cout << matrix[j][k] << " ";
            }
            cout << endl;
        }

    }
    void printDistanceMatrixWeighted() {
        std::vector<std::vector<E>> matrix;
        
        // Create Matrix
        for (int i = 0; i < verticies_.size(); i++)
        {
            matrix.push_back(shortestDijkstras(i));
        }

        // Print Matrix        
        for (int j = 0; j < verticies_.size(); j++)
        {
            for (int k = 0; k < verticies_.size(); k++)
            {
                cout << matrix[j][k] << " ";
            }
            cout << endl;
        }

    }
    ~Graph() {}
    






};
