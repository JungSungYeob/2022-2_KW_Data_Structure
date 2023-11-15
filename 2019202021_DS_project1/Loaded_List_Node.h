

#ifndef DS_PROJECT_VER3_LOADED_LIST_NODE_H
#define DS_PROJECT_VER3_LOADED_LIST_NODE_H
#include <iostream>

using namespace std;

class Loaded_List_Node {

public:
    int seq = 0; //sequence of node
    char num[4] = {'\0'}; //file_num
    char name[100] = {'\0',}; //file_name
    char dir[100];
    Loaded_List_Node *next; //next;
    Loaded_List_Node *down; //down;
    Loaded_List_Node();
};


#endif //DS_PROJECT_VER3_LOADED_LIST_NODE_H
