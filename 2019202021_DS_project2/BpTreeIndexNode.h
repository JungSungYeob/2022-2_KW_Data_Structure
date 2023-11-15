#ifndef _BPTREEINDEXNODE_H_
#define _BPTREEINDEXNODE_H_

#include "BpTreeNode.h"
//template <class T>
class BpTreeIndexNode : public BpTreeNode {
private:
    map <int, BpTreeNode*> mapIndex;

public:
    BpTreeIndexNode() {}

//insert index map
    void insertIndexMap(int n, BpTreeNode* pN) {
        mapIndex.insert(map<int, BpTreeNode*>::value_type(n, pN));
    }
//delete index map
    void deleteMap(int n) {
        mapIndex.erase(n);
    }
    //get index map
    map <int, BpTreeNode*>* getIndexMap() { return &mapIndex; }

};

#endif