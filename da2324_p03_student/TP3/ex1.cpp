// Original code by Gonçalo Leão
// Updated by DA 2023/2024 Team

#include "../data_structures/Graph.h"
using namespace std;

template <class T>
void bfsEdmondKarp(Graph<T> *g, int source, int target){
    std::queue<Vertex<T> *> q;
    Vertex<T>* s = g->findVertex(source);
    s->setVisited(true);
    q.push(s);
    while(!q.empty()){
        auto u = q.front();
        q.pop();
        if(u->getInfo()==target){break;}
        bool sat = true;
        for(Edge<T>* e : u->getAdj()){
            auto v = e->getDest();
            if(!v->isVisited() && (e->getWeight()-e->getFlow())>0){
                sat = false;
                v->setVisited(true);
                v->setPath(e);
                q.push(v);
            }
        }
        if(sat){
            for(Edge<T>* e : u->getIncoming()){
                if(e == u->getPath()) continue;
                if(e->getFlow() > 0){
                    Edge<T>* reverse = new Edge<T> (e->getDest(), e->getOrig(), e->getFlow());
                    reverse->setReverse(e);
                    e->getOrig()->setPath(reverse);
                    q.push(e->getOrig());
                    break;
                }
            }
        }
    }
}
template <class T>
void augmentPath(Graph<T> *g, int source , int target){
    auto t = g->findVertex(target);
    auto org = t->getPath();


    double bottleneck = INF;
    while(org->getOrig()->getInfo() != source){
        if((org->getWeight()-org->getFlow()) < bottleneck) bottleneck = org->getWeight()-org->getFlow();
        org = org->getOrig()->getPath();
    }

    org = t->getPath();

    while(true){
        if(org->getOrig()->getInfo() == source){
            org->setFlow(org->getFlow()+bottleneck);
            break;
        }
        else if(org->getReverse() != nullptr){
            org->getReverse()->setFlow(org->getReverse()->getFlow()-bottleneck);
            org = org->getOrig()->getPath();
            continue;
        }
        else{
        org->setFlow(org->getFlow()+bottleneck);
        org = org->getOrig()->getPath();
    }
    }
}
template <class T>
void edmondsKarp(Graph<T> *g, int source, int target) {
    for(auto v : g->getVertexSet()) {
        for(Edge<T>* e : v->getAdj()){
            e->setFlow(0);
        }
    }


    while(true){
        for(auto v : g->getVertexSet()){
            v->setVisited(false);
            v->setPath(nullptr);
        }

        bfsEdmondKarp(g, source, target);

        auto t = g->findVertex(target);
        if(!t->isVisited()) break;

        augmentPath(g, source, target);
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