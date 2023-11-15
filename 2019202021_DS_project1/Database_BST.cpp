//
// Created by 정성엽 on 2022/10/13.
//

#include "Database_BST.h"

Database_BST::Database_BST() {
    head = NULL;
    stack_root = NULL;
    queue_root = NULL;
}
Database_BST::~Database_BST() {

}
void Database_BST::Move_Create_BST(char *file_dir, char *file_name, int file_num) {
    if (count > 300) { //if BST>300
        Database_BST_Node *currNode = head;
        Database_BST_Node *prevNode;
        while (currNode->lower_next = NULL) {
            prevNode = currNode;
            currNode = currNode->lower_next;
        }
        if (currNode->upper_next != NULL) {//if currNode->next exist link prev and curr next;
            prevNode->lower_next = NULL;
            prevNode->lower_next = currNode->upper_next;
            currNode->upper_next = NULL;
            delete currNode;
        } else {
            prevNode->lower_next = NULL;
            delete currNode;
        }
    }
    //make BST
    if (head == NULL) {
        head = new Database_BST_Node;
        strcpy(head->name, file_name);
        head->num = file_num;
        strcpy(head->dir, file_dir);
    } else {
        Database_BST_Node *currNode = head;
        while (1) {
            if (currNode->num < file_num) //if BST bigger
            {
                if (currNode->upper_next != NULL) {
                    currNode = currNode->upper_next;
                    continue;
                } else {
                    currNode->upper_next = new Database_BST_Node;
                    currNode = currNode->upper_next;
                    strcpy(currNode->name, file_name);
                    currNode->num = file_num;
                    strcpy(currNode->dir, file_dir);
                    break;
                }
            } else {//if BST smaller
                if (currNode->lower_next != NULL) {
                    currNode = currNode->lower_next;
                    continue;
                } else {
                    currNode->lower_next = new Database_BST_Node;
                    currNode = currNode->lower_next;
                    strcpy(currNode->name, file_name);
                    currNode->num = file_num;
                    strcpy(currNode->dir, file_dir);
                    break;
                }
            }
        }
    }
    count++; // count for if BST over 300
}

int Database_BST::BST_exist() {
    if (head == NULL) {
        return 0;
    } else {
        return 1;
    }
}
void Database_BST::print_all() {
    print_BST_in(head);
}
void Database_BST::print_BST_in(Database_BST_Node *Node) {
    if (Node != nullptr) {
        print_BST_in(Node->lower_next);
        cout << Node->dir << "/" << Node->num << "/" << Node->name << endl;
        print_BST_in(Node->upper_next);
    }
}

void Database_BST::make_queue() {
    post_queue(head);
}

//I made post-order by recursion to see how it works.
//and I use struct to make queue for search
/*
    void tmp_post(Database_BST_Node *Node) {
        if (Node != nullptr) {
            tmp_post(Node->lower_next);
            tmp_post(Node->upper_next);
            if (queue_root == NULL) {
                queue_root = new Queue_Node;
                queue_root->num = Node->num;
                strcpy(queue_root->name, Node->name);
            } else {
                Queue_Node *tmp_Node = queue_root;
                while (tmp_Node->next != NULL) {
                    tmp_Node = tmp_Node->next;
                }
                tmp_Node->next = new Queue_Node;
                tmp_Node = tmp_Node->next;
                tmp_Node->num = Node->num;
                strcpy(tmp_Node->name, Node->name);
            }
        }
    }
*/

void Database_BST::post_queue(Database_BST_Node *Node) {
    //stack BST Node a,b
    stack<Database_BST_Node *> a, b;
    Database_BST_Node *currNode = head; //set currNode = head
    a.push(currNode);
    while (!a.empty()) { //activate until stack be empty
        currNode = a.top();
        a.pop();
        //push top element
        b.push(currNode);
        //push lower_next
        if (currNode->lower_next != NULL)
            a.push(currNode->lower_next);
        //push upper_next
        if (currNode->upper_next != NULL)
            a.push(currNode->upper_next);
    }
    //activate until stack be empty
    while (!b.empty()) {
        //make queue
        if (queue_root == NULL) {
            queue_root = new Queue_Node;
            queue_root->num = b.top()->num;
            strcpy(queue_root->name, b.top()->name);
        } else {
            Queue_Node *tmp_Node = queue_root;
            while (tmp_Node->next != NULL) {
                tmp_Node = tmp_Node->next;
            }
            tmp_Node->next = new Queue_Node;
            tmp_Node = tmp_Node->next;
            tmp_Node->num = b.top()->num;
            strcpy(tmp_Node->name, b.top()->name);
        }
        b.pop();
    }
}
void Database_BST::search_queue(char *word) {
//for Boyer Moore algorithm get strlen
    int size = strlen(word);
    Queue_Node *currNode = queue_root;
    Queue_Node *prevNode = currNode;

    while (currNode != NULL) {
        for (int i = 0; i < 100; i++) {
            int cnt = 0;
            if (currNode->name[i] == word[0]) {
                for (int j = 1; j < size; j++) {
                    if (currNode->name[i + j] == word[j]) {
                        cnt++; //count for move amount of correct
                    } else {
                        break;
                    }
                }
            } else
                continue;

            if (cnt == size - 1) //if same
            {
                cout << "\"" << currNode->name << "\" / " << currNode->num << endl;
            } else {
                i += cnt; //move i+cnt;
            }

        }
        //if checked, delete checked node
        currNode = currNode->next;
        delete prevNode;
        prevNode = currNode;
    }
}
char* Database_BST::select_BST(int num) {
    Database_BST_Node *select_Node;
    select_Node = select_BST_pre(head, num);
    if (select_Node == NULL)
        return "\0";
    return select_Node->name;
}
char* Database_BST::select_BST_dir(int num) {
    Database_BST_Node *select_Node;
    select_Node = select_BST_pre(head, num);
    return select_Node->dir;
}

Database_BST_Node* Database_BST::select_BST_pre(Database_BST_Node *Node, int num) {
    Database_BST_Node *tmp = NULL;
    if (Node != nullptr) {
        if (Node->num == num) {
            tmp = Node;
            return tmp;
        } else if (select_BST_pre(Node->lower_next, num) != NULL) {
            tmp = select_BST_pre(Node->lower_next, num);
            return tmp;
        } else if (select_BST_pre(Node->upper_next, num) != NULL) {
            tmp = select_BST_pre(Node->upper_next, num);
            return tmp;
        }
        return tmp;
    } else
        return tmp;
}