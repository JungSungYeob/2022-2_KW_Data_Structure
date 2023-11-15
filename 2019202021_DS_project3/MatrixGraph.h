//
// Created by 정성엽 on 2022/12/10.
//

#ifndef DSPRO3_MATRIXGRAPH_H
#define DSPRO3_MATRIXGRAPH_H

#include "Graph.h"

class MatrixGraph : public Graph {
private:
    int **m_Mat;
    ofstream fout;
public:
    MatrixGraph(bool type, int size);

    ~MatrixGraph();

    void getAdjacentEdges(int vertex, map<int, int> *m);

    void getDirectedEdges(int vertex, map<int, int> *m);

    void insertEdge(int from, int to, int weight);

    bool printGraph();
};

#endif //DSPRO3_MATRIXGRAPH_H
