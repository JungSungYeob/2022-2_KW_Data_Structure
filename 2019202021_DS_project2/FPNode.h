#pragma once

#include <cstring>
#include <map>
#include <cmath>
using namespace std;
class FPNode {
private:
    int frequency;
    FPNode *parent;
    FPNode *next;
    map<string, FPNode *> children;
    char *item;

public:
    FPNode();

    ~FPNode();

    void setParent(FPNode *node) {
        this->parent = node;
    }

    void setNext(FPNode *node) {
        next = node;
    }

    void pushchildren(string item, FPNode *node) {
        children.insert(map<string, FPNode *>::value_type(item, node));
    }

    void updateFrequency(int frequency) {
        this->frequency += frequency;
    }

    void setitem(char *item) {
        strcpy(this->item, item);
    }

    int getFrequency() { return frequency; }

    FPNode *getParent() { return parent; }

    FPNode *getNext() { return next; }

    FPNode *getChildrenNode(string item);

    map<string, FPNode *> getChildren() { return children; }

    char *get_Item() {
        return item;
    }
};


