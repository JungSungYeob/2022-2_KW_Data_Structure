//
// Created by 정성엽 on 2022/10/13.
//

#ifndef DS_PROJECT_VER3_DATABASE_BST_H
#define DS_PROJECT_VER3_DATABASE_BST_H
#include <iostream>
#include <cstring>
#include <unistd.h>
#include <string>
#include <fstream>

#include "Stack_Node.h"
#include "Queue_Node.h"
#include "Database_BST_Node.h"

using namespace std;

class Database_BST {
private:
    Stack_Node *stack_root;
    Queue_Node *queue_root;
    Database_BST_Node *head;
    int count = 0;
public:
    Database_BST();
    ~Database_BST();
    void Move_Create_BST(char *file_dir, char *file_name, int file_num);
    int BST_exist();
    void print_all();
    void print_BST_in(Database_BST_Node *Node);
    void make_queue();
    void post_queue(Database_BST_Node *Node);
    void search_queue(char *word);
    char* select_BST(int num);
    char* select_BST_dir(int num);

    Database_BST_Node *select_BST_pre(Database_BST_Node *Node, int num);
};


#endif //DS_PROJECT_VER3_DATABASE_BST_H
