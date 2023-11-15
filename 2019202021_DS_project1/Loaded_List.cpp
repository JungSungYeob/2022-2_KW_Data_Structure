//
// Created by 정성엽 on 2022/10/13.
//

#include "Loaded_List.h"

Loaded_List::Loaded_List() {
    img_files = NULL, new_files = NULL; //set directory NULL
    //set new Node of directory
    img_files = new Loaded_List_Node;
    img_files->next = NULL;
    img_tail = img_files;
    new_files = new Loaded_List_Node;
    new_files->next = NULL;
    new_tail = new_files;
    //link img_files and new_files
    img_files->down = new_files;
}
Loaded_List::~Loaded_List() {
    delete_img_files();
    delete_img_files();
    delete img_files;
    delete new_files;
}
void Loaded_List::InsertNode(int index, char *file_name, char *file_num) {
//if count >100, delete Node which have smaller seq
    if (count >= 100) {
        Loaded_List_Node *deleteNode;
        if (img_files->next->seq < new_files->next->seq) {
            deleteNode = img_files->next;
            img_files->next = deleteNode->next;
            delete deleteNode;
        } else {
            deleteNode = new_files->next;
            new_files->next = deleteNode->next;
            delete deleteNode;
        }
    }
    //load or add or modify
    if (index == 0) //load
    {
        img_tail->next = new Loaded_List_Node;
        img_tail = img_tail->next;
        img_tail->seq = count;
        strcpy(img_tail->name, file_name);
        cout << img_tail->name;
        strcpy(img_tail->num, file_num);
        cout << "/" << img_tail->num << "\n";
    } else if (index == 1)//add
    {
        new_tail->next = new Loaded_List_Node;
        new_tail = new_tail->next;
        new_tail->seq = count;
        strcpy(new_tail->name, file_name);
        cout << new_tail->name;
        strcpy(new_tail->num, file_num);
        cout << "/" << new_tail->num << endl;
    }
    count++;
}
void Loaded_List::delete_img_files() {
    Loaded_List_Node *currNode = img_files->next;
    img_tail = img_files;
    Loaded_List_Node *prevNode;
    while (currNode != NULL) {
        prevNode = currNode;
        currNode = currNode->next;
        prevNode->next = NULL;
        delete prevNode;
    }
}
void Loaded_List::delete_new_files() {
    Loaded_List_Node *currNode = new_files->next;
    new_tail = new_files;
    Loaded_List_Node *prevNode;
    while (currNode != NULL) {
        prevNode = currNode;
        currNode = currNode->next;
        prevNode->next = NULL;
        delete prevNode;
    }
}
void Loaded_List::find_name(Loaded_List_Node *node_name, char *file_name, char*file_num) {
    Loaded_List_Node *currNode = node_name;
    Loaded_List_Node *prevNode;
    int seq; //to get seq to remake
    bool find = false;
    while (currNode->next != NULL) { //currNode will move until end
        if (strcmp(currNode->name, file_name) == 0) { //if I find same sentence
            find = true;
            //input information
            seq = currNode->seq;
            prevNode->next = NULL;
            prevNode->next = new Loaded_List_Node;
            prevNode = prevNode->next;
            prevNode->next = currNode->next;
            currNode->next = NULL;
            //delete existing Node
            delete currNode;
            prevNode->seq = seq;
            strcpy(prevNode->name, file_name);
            strcpy(prevNode->num, file_num);
            //input dir each
            if (node_name == img_files)
                strcpy(prevNode->dir, "img_files");
            else
                strcpy(prevNode->dir, "new_files");

        } else {//move next;
            prevNode = currNode;
            currNode = currNode->next;
        }
    }
    if (find == false) { //if can't find
        cout << "=======ERROR=======" << endl;
        cout << "300" << endl;
        cout << "==================" << endl;
    }
    if (find == true) { //if find
        cout << "=======MODIFY=======" << endl;
        cout << "Success" << endl;
        cout << "==================" << endl;
    }
}
void Loaded_List::ModifyNode(int index, char *file_name, char *file_num) {
    if (index == 0) {
        find_name(img_files, file_name, file_num);
        /*Loaded_List_Node * currNode = img_files->next;
        while(currNode!=NULL)
        {
            cout << currNode->num << endl;
            currNode=currNode->next;
        }*/
    }
    if (index == 1) {
        find_name(new_files, file_name, file_num);
    }
}
int Loaded_List::return_dir() {
    if (img_tail->seq < new_tail->seq) {
        return 1;
    } else if (img_tail->seq > new_tail->seq) {
        return 0;
    } else if (img_files->next == NULL && new_files->next != NULL) {
        return 1;
    } else if (img_files->next != NULL && new_files->next == NULL) {
        return 0;
    } else if (img_files->next == NULL && new_files->next == NULL) {
        return -1;
    }
}
char* Loaded_List::return_name(int index) {
    if (index == 0) {
        return img_tail->name;
    } else if (index == 1) {
        return new_tail->name;
    }
}
int Loaded_List::return_num(int index) {
    char tmp_num[4];
    int num;
    if (index == 0) {
        strcpy(tmp_num, img_tail->num);
    } else if (index == 1) {
        strcpy(tmp_num, new_tail->num);
    }
    num = (tmp_num[0] - 48) * 100 + (tmp_num[1] - 48) * 10 + (tmp_num[2] - 48);
    return num;
}
void Loaded_List::delete_tail(int index) {
    Loaded_List_Node *deleteNode;
    if (index == 0) {
        Loaded_List_Node *currNode = img_files;
        while (currNode->next != img_tail) {
            currNode = currNode->next;
        }
        deleteNode = currNode->next;
        img_tail = currNode;
        delete deleteNode;
        currNode->next = NULL;
    } else if (index == 1) {
        Loaded_List_Node *currNode = new_files;
        while (currNode->next != new_tail) {
            currNode = currNode->next;
        }
        deleteNode = currNode->next;
        new_tail = currNode;
        delete deleteNode;
        currNode->next = NULL;
    }
}