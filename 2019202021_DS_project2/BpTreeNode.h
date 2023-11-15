#pragma once
#include "FrequentPatternNode.h"
#include "FPNode.h"
class BpTreeNode//parent class of Bptree's class
{
private:
    BpTreeNode* pParent;
    BpTreeNode* pMostLeftChild;

public:
    BpTreeNode() {//constructor
        pParent = NULL;
        pMostLeftChild = NULL;
    }
    ~BpTreeNode() {

    }
    //set left child node
    void setMostLeftChild(BpTreeNode* pN) { pMostLeftChild = pN; }
    //set parent node
    void setParent(BpTreeNode* pN) { pParent = pN; }
    //get parent node
    BpTreeNode* getParent() { return pParent; }
    //get left child
    BpTreeNode* getMostLeftChild() { return pMostLeftChild; }
    //declare virtual function and nodes
    virtual void setNext(BpTreeNode* pN) {}
    virtual void setPrev(BpTreeNode* pN) {}
    virtual BpTreeNode* getNext() { return NULL; }
    virtual BpTreeNode* getPrev() { return NULL; }
    //declare virtual function and insert data or index and deletemap
    virtual void insertDataMap(int n, FrequentPatternNode* pN) {}
    virtual void insertIndexMap(int n, BpTreeNode* pN) {}
    virtual void deleteMap(int n) {}
    //declare virtual function about indexnode or datanode
    virtual map<int, BpTreeNode*>* getIndexMap() { return {}; }
    virtual map<int, FrequentPatternNode*>* getDataMap() { return {}; }

};
