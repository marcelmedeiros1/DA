#include <iostream>
#include "../data_structures/Graph.h"
#include <stack>

using namespace std;
template <typename T>

/****************** toposort ********************/
/*
 * Performs a topological sorting of the vertices of a graph.
 * Returns a vector with the contents of the vertices by topological order.
 * If the graph has cycles, returns an empty vector.
 * Follows the algorithm described in theoretical classes.
 */
vector<T> topsort(const Graph<T>* g) {
    for(Vertex<T>* v : g->getVertexSet()) v->setIndegree(0);
    for(Vertex<T>* v : g->getVertexSet()){
        for(Edge<T> e : v->getAdj()){
            Vertex<T>* u = e.getDest();
            u->setIndegree(u->getIndegree()+1);
        }
    }
    vector<T> res;
    queue<Vertex<T>*> q;

    for(Vertex<T>* v : g->getVertexSet()){
        if(v->getIndegree()==0){
            q.push(v);
            v->setVisited(true);
        }
    }
    while(!q.empty()){
        Vertex<T>* u = q.front();
        for(const Edge<T>& e : u->getAdj()){
            Vertex<T>* v = e.getDest();
            v->setIndegree(v->getIndegree()-1);
            if(v->getIndegree()==0) {
                q.push(v);
                v->setVisited(true);
            }
        }
        q.pop();
        res.push_back(u->getInfo());
    }

    return res;
}