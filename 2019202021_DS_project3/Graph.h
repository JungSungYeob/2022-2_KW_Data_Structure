//
// Created by 정성엽 on 2022/12/10.
//

#ifndef DSPRO3_GRAPH_H
#define DSPRO3_GRAPH_H

#include <iostream>
#include <cstring>
#include <string.h>
#include <fstream>
#include <map>
#include <set>
#include <math.h>
#include <vector>
#include <algorithm>
#include <deque>
#include <queue>
#include <stack>

using namespace std;

#define MAX 999999

class Graph {
protected:
    bool m_Type;//0:List 1:Matrix
    int m_Size;

public:
    Graph(bool type, int size);

    virtual ~Graph()=0;

    bool getType();

    int getSize();

    virtual void getAdjacentEdges(int vertex, map<int, int> *m) = 0;

    virtual void getDirectedEdges(int vertex, map<int, int> *m) = 0;

    virtual void insertEdge(int from, int to, int weight) = 0;

    virtual bool printGraph() = 0;
};

#endif //DSPRO3_GRAPH_H
