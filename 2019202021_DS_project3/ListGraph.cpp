//
// Created by 정성엽 on 2022/12/10.
//

#include "ListGraph.h"

ListGraph::ListGraph(bool type, int size) : Graph(type, size) {
    fout.open("log.txt", ios::app);
    m_Type = type;
    m_List = new map<int, int>[size];
}

ListGraph::~ListGraph() {
    delete[] m_List;
}

void ListGraph::getAdjacentEdges(int vertex, map<int, int> *m) {
    for (int i = 0; i < m_Size; i++) {
        for (auto it_ = m_List[i].begin(); it_ != m_List[i].end(); it_++) {
            if (vertex == it_->first)
                m[vertex].insert(make_pair(i, it_->second));
            if (vertex == i)
                m[vertex].insert(make_pair(it_->first, it_->second));
        }
    }
}

void ListGraph::getDirectedEdges(int vertex, map<int, int> *m) {
    for (auto it_ = m_List[vertex].begin(); it_ != m_List[vertex].end(); it_++) {
        m[vertex].insert(make_pair(it_->first, it_->second));
    }
}

void ListGraph::insertEdge(int from, int to, int weight) {
    m_List[from].insert(make_pair(to, weight));
}

bool ListGraph::printGraph() {
    //cout << "Graph is ListGraph!" << endl;
    fout << "==========PRINT==========" << endl;
    for (int i = 0; i < m_Size; i++) {
        //cout << "[" << i << "]";
        fout << "[" << i << "]";
        for (auto it_ = m_List[i].begin(); it_ != m_List[i].end(); it_++) {
            //cout << "(" << it_->first << "," << it_->second << ")";
            fout << " -> " << "(" << it_->first << "," << it_->second << ")";
        }
        //cout << endl;
        fout << endl;
    }
   // cout << endl;
    fout << endl;
    fout << "=========================" << endl;
    return 1;
}
