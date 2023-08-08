
#include <cstddef>   
#include <iostream>
#include <vector>
#include <queue>
#include <cmath>

using namespace std;
template<typename T, typename E>
/*
* Directed Graph

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
    std::vector<int> in_degs_; // in degree of each vertex


    size_t addVertex(T value)   
    {
        Vertex<T> new_vertex(std::forward<T>(value), this->verticies_.size());
        verticies_.push_back(new_vertex);
        in_degs_.push_back(0);
        neighbors_.resize(verticies_.size());
        return new_vertex.getID();
    };

    void addEdge(size_t v1, size_t v2, E distance)
    {
        in_degs_[v2]++;
        Vertex<T> v2_copy = verticies_[v2];
        v2_copy.distance_ = distance;
        neighbors_[v1].push_back(v2_copy);
        cout << "in degree of " << verticies_[v2].element_ << " is " << in_degs_[v2] << endl;
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

    bool verticiesDone(std::vector<bool> &vec, int value_that_means_its_not_done)
    {
        for (auto i : vec) {
            if (i == value_that_means_its_not_done)
            {
                return false;
            }

        }

        return true;
    }
    std::vector<E> shortestDijkstras(size_t source,std::vector<size_t>& path )
    {
        std::vector<E> distance(verticies_.size(), INFINITY);
        //std::vector<size_t> path(verticies_.size(), 0);
        std::vector<bool> done(verticies_.size(), false);
        distance[source] = 0;
        Vertex<T> v = verticies_[0];
        while (!verticiesDone(done,0))
        {
            //cout << "verticies not done" << endl;
            
            // pick next vertex to work on
            // get a comparison vertex that's not done:
            while (done[v.getID()])
            {
                if (v.getID() == (verticies_.size()-1))
                {
                    v = verticies_[0];
                }
                else
                {
                    v = verticies_[v.getID() + 1];
                } 
            }
            for (auto i : this->verticies_)
            {
                //cout << "checking if i is smaller" << endl;
                if ((distance[i.getID()] < distance[v.getID()]) && (done[i.getID()] == false))
                {
                    v = i;
                    //cout << "updating v, v is " << v.element_ << endl;

                }
            }

            //cout << "element value: " << v.getValue() << endl;
            for (auto n : neighbors_[v.getID()])
            {
                E weight = n.distance_;
                if (weight != 15.3) 
                {
                    //cout << "weight " << weight << endl;
                }

                if (!done[n.getID()])
                {
                    E dist = distance[v.getID()] + n.distance_;
                    //cout << "dist " << dist << endl;
                    if (distance[n.getID()] > dist)
                    {
                        distance[n.getID()] = dist;
                        path[n.getID()] = v.getID();
                        //cout << "updated: " << v.element_ << "'s neighbor " << n.element_  << " with total dist " << dist << endl;
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
        std::vector<size_t> path(verticies_.size(), 0);
        // Create Matrix
        for (int i = 0; i < verticies_.size(); i++)
        {
            matrix.push_back(shortestDijkstras(i, path));
        }

        // Print Elements
        for (int j = 0; j < path.size(); j++)
        {
            cout << path[j] << " ";
        }
        cout << endl;

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
    bool verticiesDoneTopo(std::vector<bool> &vec, int value_that_means_its_done)
    {
        for (auto i : vec) {
            if (i != value_that_means_its_done)
            {
                return false;
            }

        }

        return true;
    }
    void topoSort()
    {
        vector<int> degrees_copy = this->in_degs_;
        //vector<size_t> finished;
        queue<size_t> worklist;

        // find a vertex with in degree 0
        Vertex<T> v = verticies_[0];
        while(degrees_copy[v.getID()] != 0)
        {
            if (v.getID() == verticies_.size())
            {
                cout << " No verticies with in degree of 0, can't do topological sort" << endl;
                return;
            }
            v = verticies_[v.getID() + 1];
            
        }

        // v has in-degree of 0, so no predessesors, so we can add it to the worklist
        worklist.push(v.getID());

        cout << "Topo Sort: ";
        while (!worklist.empty())
        {
            size_t current_v = worklist.front();

            // decrement the in degree of it's neighbors, and add them to the worklist if their in degree is now 0
            for (auto n: neighbors_[current_v])
            {
                degrees_copy[n.getID()]--;
                if (degrees_copy[n.getID()] == 0)
                {
                    worklist.push(n.getID());
                }
            }

            // visit the current vertex
            cout << verticies_[current_v].element_ << ", " ;
            // remove the current vertex from the worklist, it's done now
            worklist.pop();

        }
        cout << endl;




    }

    ~Graph() {}
    






};
