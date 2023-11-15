//
// Created by 정성엽 on 2022/10/13.
//

#ifndef DS_PROJECT_VER3_LOADED_LIST_H
#define DS_PROJECT_VER3_LOADED_LIST_H
#include <iostream>
#include "Loaded_List_Node.h"

class Loaded_List {
private:
    Loaded_List_Node *img_files; //Node directory img_files
    Loaded_List_Node *img_tail; //Node img_tail
    Loaded_List_Node *new_files; //Node director new_files
    Loaded_List_Node *new_tail; //Node new_tail
    int count = 0; //count amount of Node
    bool loaded = false; //record if command have executed LOAD
    bool added = false; //record if command have executed ADD
public:
    Loaded_List();
    ~Loaded_List();
    void InsertNode(int index, char *file_name, char *file_num);
    void delete_img_files();
    void delete_new_files();
    void find_name(Loaded_List_Node *node_name, char *file_name,char*file_num);
    void ModifyNode(int index, char *file_name, char *file_num);
    int return_dir();
    char *return_name(int index);
    int return_num(int index);
    void delete_tail(int index);
};


#endif //DS_PROJECT_VER3_LOADED_LIST_H
