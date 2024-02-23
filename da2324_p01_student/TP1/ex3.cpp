#include "../data_structures/Graph.h"
#include "stack"
using namespace std;

// Helper function to reverse the edges of a directed graph
template <typename T>
void aux_reverseGraphEdges(Graph<T>* g) {
    for(Vertex<T>* v : g){
        for(Edge<T> e : v->getAdj()){
            g->addEdge(e.getDest()->getInfo(), v->getInfo(), NULL);
            g->removeEdge(v->getInfo(), e.getDest()->getInfo());
        }
    }
}

// Kosaraju-Sharir algorithm to find strongly connected components
template <typename T>
vector<vector<T>> SCCkosaraju(Graph<T>* g)  {
    vector<vector<T>> sccs;

    return sccs;
}

// First depth-first search in Kosaraju-Sharir algorithm
template <typename T>
void firstDFSKosarajuSharir(Vertex<T> *v, stack<Vertex <T> *> *vertexStack)  {
    // TODO
}

// Second depth-first search in Kosaraju-Sharir algorithm
template <typename T>
void secondDFSKosarajuSharir(Vertex<T> *v, std::vector<int> & res)  {
    // TODO
}
