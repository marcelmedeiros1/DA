// Original code by Gonçalo Leão
// Updated by DA 2023/2024 Team

#include "MSTTestAux.h"
#include "../data_structures/UFDS.h"

template <class T>
void dfsKruskalPath(Vertex<T> *v) {
    // TODO
}
template <class T>
bool compareEdgesByWeight(Edge<T>* a, Edge<T>* b) {
    return a->getWeight() < b->getWeight();
}

template <class T>
std::vector<Vertex<T> *> kruskal(Graph<T> *g) {
    UFDS ufds(g->getVertexSet().size()); {
        int id=0;
        for(Vertex<T>* v : g->getVertexSet()) v->setInfo(id++);
    }
    vector<Vertex<T>*> res;
    vector<Edge<T>*> edges;

    for(Vertex<T>* v : g->getVertexSet()){
        v->setVisited(false);
        v->setPath(nullptr);
        for(Edge<T>* e : v->getAdj()){
            edges.push_back(e);
        }
    }

    sort(edges.begin(), edges.end(), compareEdgesByWeight<T>);
    for(Edge<T>* e : edges){
        Vertex<T>* u = e->getOrig();
        Vertex<T>* v = e->getDest();
        if(u->isVisited() && v->isVisited()) continue;
        if(!ufds.isSameSet(u->getInfo(), v->getInfo())){
            res.push_back(u);
            res.push_back(v);
            v->setPath(e);
            u->setVisited(true);
            v->setVisited(true);
            ufds.linkSets(u->getInfo(), v->getInfo());
        }
    }

    return res;
}

/// TESTS ///
#include <gtest/gtest.h>

TEST(TP3_Ex3, test_kruskal) {
    Graph<int> graph = createMSTTestGraph<int>();
    std::vector<Vertex<int> *> res = kruskal(&graph);

    std::stringstream ss;
    for(const auto v : res) {
        ss << v->getInfo() << "<-";
        if ( v->getPath() != nullptr ) {
            ss << v->getPath()->getOrig()->getInfo();
        }
        ss << "|";
    }
    std::cout << ss.str() << std::endl;

    EXPECT_TRUE(isSpanningTree(res));
    EXPECT_EQ(spanningTreeCost(res), 11);
}