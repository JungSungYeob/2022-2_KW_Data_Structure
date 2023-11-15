//
// Created by 정성엽 on 2022/10/13.
//

#ifndef DS_PROJECT_VER3_DATABASE_BST_NODE_H
#define DS_PROJECT_VER3_DATABASE_BST_NODE_H


class Database_BST_Node {
public:
    Database_BST_Node *upper_next; //bst upper
    Database_BST_Node *lower_next; //bst lower
    char dir[15]; //directory
    char name[100]; //file_name
    int num; //file_num
};


#endif //DS_PROJECT_VER3_DATABASE_BST_NODE_H
