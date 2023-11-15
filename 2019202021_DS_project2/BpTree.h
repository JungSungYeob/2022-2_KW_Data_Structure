#ifndef _BpTree_H_
#define _BpTree_H_

#include "BpTreeDataNode.h"
#include "BpTreeIndexNode.h"
#include <fstream>
#include <iostream>

class BpTree {
private:
    BpTreeNode* root;//root node
    int			order;		// m children
    ofstream* fout;//write log file
public:
    BpTree(ofstream *fout, int order = 3) {
        root = NULL;
        this->order = order;
        this->fout = fout;
    }
    /* essential */
    bool		Insert(int key, set<string> set);//insert bptree
    bool		excessDataNode(BpTreeNode* pDataNode);//goto datanode
    bool		excessIndexNode(BpTreeNode* pIndexNode);//goto indexnode
    void		splitDataNode(BpTreeNode* pDataNode);//split datanode
    void		splitIndexNode(BpTreeNode* pIndexNode);//split index node
    BpTreeNode* getRoot() { return root; }//get root and return
    BpTreeNode* searchDataNode(int n);//search data node
//print function for pattern frequency confidence range
    void	printFrequentPatterns(set<string> pFrequentPattern, string item);
    bool	printFrequency(string item, int min_frequency);
    bool	printConfidence(string item, double item_frequency, double min_confidence);
    bool 	printRange(string item, int min, int max);

};

#endif
