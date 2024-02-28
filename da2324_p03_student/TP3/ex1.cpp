// Original code by Gonçalo Leão
// Updated by DA 2023/2024 Team

#include "../data_structures/Graph.h"

using namespace std;

template <class T>
void edmondsKarp(Graph<T> *g, int source, int target) {
    for(auto v : g->getVertexSet()) {
        for(auto e : v->getAdj()){
            e->setFlow(0);
        }
    }

    while(true){
        for(auto v : g->getVertexSet()){
            v->setVisited(false);
            v->setPath(nullptr);
        }
        /*vector<Vertex<T>*> path;
        while(!q.empty()){
            Vertex<T>* v = q.front();
            q.pop();
            path.push_back(v);
            for(Edge<T>* e : v->getAdj()){
                if((e->getWeight()-e->getFlow()) > 0){
                Vertex<T>* w = e->getDest();
                if(! w->isVisited()){
                    q.push(w);
                    w->setVisited(true);
                }
            }
            }

        }*/
        queue<Vertex<T> *> q;
        Vertex<T>* s = g->findVertex(source);
        s->setVisited(true);
        q.push(s);
        while(!q.empty()){
            auto u = q.front();
            q.pop();
            if(u->getInfo()==target) break;
            for(auto e : u->getAdj()){
                auto v = e->getDest();
                if(!v->isVisited() && (e->getWeight()-e->getFlow())>0){
                    v->setVisited(true);
                    v->setPath(e);
                    q.push(v);
                }
            }
        }
        auto t = g->findVertex(target);
        if(!t->isVisited()) break;
        while(true){
            auto org = t->getIncoming();
        }

    }
}

/// TESTS ///
#include <gtest/gtest.h>

TEST(TP3_Ex1, test_edmondsKarp) {
    Graph<int> myGraph;

    for(int i = 1; i <= 6; i++)
        myGraph.addVertex(i);

    myGraph.addEdge(1, 2, 3);
    myGraph.addEdge(1, 3, 2);
    myGraph.addEdge(2, 5, 4);
    myGraph.addEdge(2, 4, 3);
    myGraph.addEdge(2, 3, 1);
    myGraph.addEdge(3, 5, 2);
    myGraph.addEdge(4, 6, 2);
    myGraph.addEdge(5, 6, 3);

    edmondsKarp(&myGraph, 1, 6);

    std::stringstream ss;
    for(auto v : myGraph.getVertexSet()) {
        ss << v->getInfo() << "-> (";
        for (const auto e : v->getAdj())
            ss << (e->getDest())->getInfo() << "[Flow: " << e->getFlow() << "] ";
        ss << ") || ";
    }

    std::cout << ss.str() << std::endl << std::endl;

    EXPECT_EQ("1-> (2[Flow: 3] 3[Flow: 2] ) || 2-> (5[Flow: 1] 4[Flow: 2] 3[Flow: 0] ) || 3-> (5[Flow: 2] ) || 4-> (6[Flow: 2] ) || 5-> (6[Flow: 3] ) || 6-> () || ", ss.str());

}