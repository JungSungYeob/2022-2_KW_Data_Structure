//
// Created by 정성엽 on 2022/12/10.
//

#ifndef DSPRO3_LISTGRAPH_H
#define DSPRO3_LISTGRAPH_H

#include "Graph.h"

class ListGraph : public Graph {
private:
    ofstream fout;
    map<int, int> *m_List;

public:
    ListGraph(bool type, int size);

    ~ListGraph();

    void getAdjacentEdges(int vertex, map<int, int> *m);

    void getDirectedEdges(int vertex, map<int, int> *m);

    void insertEdge(int from, int to, int weight);

    bool printGraph();
};

#endif //DSPRO3_LISTGRAPH_H
