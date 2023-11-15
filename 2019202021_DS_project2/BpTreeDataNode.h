#ifndef _BpTreeDataNode_H_
#define _BpTreeDataNode_H_

#include "BpTreeNode.h"
class BpTreeDataNode : public BpTreeNode//node for data
{
private:
    map <int, FrequentPatternNode*> mapData;
    BpTreeNode* pNext;
    BpTreeNode* pPrev;
public:
    BpTreeDataNode() {
        pNext = NULL;
        pPrev = NULL;
    }
//virtual function of next and prev node
    void setNext(BpTreeNode* pN) { pNext = pN; }
    void setPrev(BpTreeNode* pN) { pPrev = pN; }
    BpTreeNode* getNext() { return pNext; }
    BpTreeNode* getPrev() { return pPrev; }
//insert data map
    void insertDataMap(int n, FrequentPatternNode* pN) {
        mapData.insert(map<int, FrequentPatternNode*>::value_type(n, pN));
    }
//delete data map
    void deleteMap(int n) {
        mapData.erase(n);
    }
    //get data map
    map<int, FrequentPatternNode*>* getDataMap() { return &mapData; }
};

#endif
