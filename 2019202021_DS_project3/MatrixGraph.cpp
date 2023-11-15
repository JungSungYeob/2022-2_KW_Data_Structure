//
// Created by 정성엽 on 2022/12/10.
//

#include "MatrixGraph.h"

MatrixGraph::MatrixGraph(bool type, int size) : Graph(type, size) {
    fout.open("log.txt", ios::app);
    m_Mat = new int *[size];
    for (int i = 0; i < size; i++) {
        m_Mat[i] = new int[size];
        memset(m_Mat[i], 0, sizeof(int) * size);
    }
}

MatrixGraph::~MatrixGraph() {
    for (int i = 0; i < getSize(); i++) {
        delete[] m_Mat[i];
    }
    delete[] m_Mat;
}

void MatrixGraph::getAdjacentEdges(int vertex, map<int, int> *m) {
    for(int i=0;i<m_Size;i++){
        for(int j=0;j<m_Size;j++){
            if(m_Mat[i][j]!=0&&j==vertex)
                m[vertex].insert(std::make_pair(i,m_Mat[i][j]));
            if(m_Mat[i][j]!=0&&i==vertex)
                m[vertex].insert(std::make_pair(j,m_Mat[i][j]));
        }
    }
}

void MatrixGraph::getDirectedEdges(int vertex, map<int, int> *m) {
    for(int i=0;i<m_Size;i++){
        if(m_Mat[vertex][i]!=0)
            m[vertex].insert(std::make_pair(i,m_Mat[vertex][i]));
    }

}

void MatrixGraph::insertEdge(int from, int to, int weight) {
    m_Mat[from][to] = weight;
}

bool MatrixGraph::printGraph() {
    if (m_Size < 0)
        return 0;

    //cout << "Graph is MatrixGraph!" << endl;
    //cout << '\t';
    fout << "==========PRINT==========" << endl;
    fout << '\t';
    for (int i = 0; i < m_Size; i++) {
        //cout << "[" << i << "]" << '\t';
        fout << "[" << i << "]" << '\t';
    }
   // cout << endl;
    fout << endl;

    for (int i = 0; i < m_Size; i++) {
        //cout << "[" << i << "]";
        fout << "[" << i << "]";
        for (int j = 0; j < m_Size && cout << '\t'; j++) {
            //cout << m_Mat[i][j];
            fout << "\t" << m_Mat[i][j];
        }
      //  cout << endl;
        fout << endl;
    }
    fout << "========================="<<endl;
    return 1;
}
