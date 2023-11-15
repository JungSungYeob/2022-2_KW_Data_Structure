//
// Created by 정성엽 on 2022/10/13.
//

#ifndef DS_PROJECT_VER3_MANAGER_H
#define DS_PROJECT_VER3_MANAGER_H
#include "Stack_Node.h"
#include "Queue_Node.h"
#include "Loaded_List.h"
#include "Database_BST.h"
#include <iostream>


using namespace std;

class Manager {
private:
    int file_num = '\0';
    char file_name2[100];
    char file_dir[100];
    bool loaded = false;
    bool added = false;
    //make stack&queue root for EDIT
    Stack_Node *stack_root = NULL;
    Queue_Node *queue_root = NULL;
public:
    class Loaded_List loadedList;
    class Database_BST databaseBst;
    void LOAD();
    void ADD();
    void MODIFY();
    void MOVE();
    void PRINT();
    void SEARCH();
    void SELECT();
    void EDIT();
};


#endif //DS_PROJECT_VER3_MANAGER_H
