#include <list>
#include "../data_structures/Graph.h"
#include "stack"
using namespace std;

template <typename T>
list<list<T>> sccTarjan( Graph<T>* g) {
    for(Vertex<T>* v : g->getVertexSet()) v->setVisited(false);
    list<list<T>> res;
    int i = 1;
    stack<T> s = {};
    for(Vertex<T>* v : g->getVertexSet()){
        if(!v->isVisited()){
            dfs_scc(g, v, s, res, i);
        }
    }
    return res;
}

template <typename T>
void dfs_scc(Graph<T> *g, Vertex<T> *v, stack<T> &s, list<list<T>> &l, int &i){
    v->setVisited(true);
    v->setNum(i);
    v->setLow(i);
    i+=1;
    s.push(v->getInfo());
    for(Edge<T> e : v->getAdj()){
        Vertex<T>* w = e.getDest();
        if(!w->isVisited()){
            dfs_scc(g, w, s, l, i);
            v->setLow(min(v->getLow(), w->getLow()));
        }
        bool flag = false;
        stack<T> cps = s;
        while(!cps.empty()){
            if(cps.top() == w->getInfo()){
                flag = true;
                break;
            }
            else{
                cps.pop();
            }
        }
        if(flag){
            v->setLow(min(v->getLow(), w->getNum()));
        }
    }
    if(v->getNum() == v->getLow()){
        list<T> c;
        T w;
        do{
            w = s.top();
            s.pop();
            c.push_back(w);
        } while(w != v->getInfo());
        l.push_back(c);
    }
}