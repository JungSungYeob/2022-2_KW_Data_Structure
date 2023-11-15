#include <iostream>
#include "Manager.h"

using namespace std;
int main() {
    class Manager manager;
    char command[10];
    while (1) {
        cout << "Input Command :";
        cin >> command;

        if (strcmp(command, "LOAD") == 0) {
            manager.LOAD();

        } else if (strcmp(command, "ADD") == 0) {
            manager.ADD();

        } else if (strcmp(command, "MODIFY") == 0) {
            manager.MODIFY();

        } else if (strcmp(command, "MOVE") == 0) {
            manager.MOVE();

        } else if (strcmp(command, "PRINT") == 0) {
            manager.PRINT();

        } else if (strcmp(command, "SEARCH") == 0) {
            manager.SEARCH();

        } else if (strcmp(command, "SELECT") == 0) {
            manager.SELECT();

        } else if (strcmp(command, "EDIT") == 0) {
            manager.EDIT();

        } else if (strcmp(command, "EXIT") == 0) {
            cout << "=======EXIT=======" << endl;
            cout << "Success" << endl;
            cout << "==================" << endl;
            break;
        } else {
            cout << "=======ERROR=======" << endl;
            cout << "777" << endl;
            cout << "==================" << endl;
        }
    }
    return 0;
}
