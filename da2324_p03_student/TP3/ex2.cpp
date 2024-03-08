// Original code by Gonçalo Leão
// Updated by DA 2023/2024 Team

#include "../data_structures/Graph.h"
#include "MSTTestAux.h"

template <class T>
std::vector<Vertex<T> *> prim(Graph<T> * g) {
    vector<Vertex<T>*> res;
    MutablePriorityQueue<Vertex<T>> A;
    for(Vertex<T>* v : g->getVertexSet()) {
        v->setVisited(false);
        v->setDist(INF);
        v->setPath(nullptr);
        A.insert(v);
    }

    Vertex<T>* s = A.extractMin();
    s->setDist(0);
    s->setPath(nullptr);
    A.insert(s);

    while(!A.empty()){
        Vertex<T>* u = A.extractMin();
        u->setVisited(true);
        res.push_back(u);
        for(Edge<T>* e : u->getAdj()){
            Vertex<T>* v = e->getDest();
            if(v->isVisited()) continue;
            if(e->getWeight() < v->getDist()){
                v->setPath(e);
                v->setDist(e->getWeight());
            }
        }
    }

    return g->getVertexSet();
}

/// TESTS ///
#include <gtest/gtest.h>

TEST(TP3_Ex2, test_prim) {
    Graph<int> graph = createMSTTestGraph<int>();
    std::vector<Vertex<int> *> res = prim(&graph);

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