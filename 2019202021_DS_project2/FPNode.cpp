#include "FPNode.h"

FPNode::FPNode()    //constructor
{
    parent = NULL;
    next = NULL;
    frequency = 0;
    item = new char[100];
    memset(item,0,100);

}


FPNode::~FPNode()//destructor
{
    delete[] item;
}

//return chile node if item exist
FPNode *FPNode::getChildrenNode(string item) {
    map<string, FPNode *>::iterator last = children.find(item);
    if (last == children.end()) return NULL;
    FPNode *findNode = last->second;
    return findNode;//return chile
}


