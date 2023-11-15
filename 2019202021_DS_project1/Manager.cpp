//
// Created by 정성엽 on 2022/10/13.
//

#include "Manager.h"

void Manager::LOAD() {
    if (loaded == true)
        loadedList.delete_img_files();
    string filePath = "img_files/filesnumbers.csv";
    if (access(filePath.c_str(), F_OK) == 0) {
        cout << "=======LOAD=======" << endl;
        string str;
        ifstream file(filePath);
        int cnt = 0;
        //get line by line
        while (getline(file, str)) {
            char ch[str.length()];
            strcpy(ch, str.c_str());
            //seperate by ","
            char *num = strtok(ch, ",");
            //seperate by "."
            char *name = strtok(NULL, ".");
            //because of zwnbsp(BOM) fix my num array for 4times
            //first *num= "???101"
            if (cnt == 0) {
                cnt++;
                num[0] = num[3];
                num[1] = num[4];
                num[2] = num[5];
                num[3] = '\0';
            }
            loadedList.InsertNode(0, name, num);
        }
        cout << "==================" << endl;
        loaded = true; //check loaded
    } else {
        cout << "=======ERROR=======" << endl;
        cout << "100" << endl;
        cout << "===================" << endl;
    }
}
void Manager::ADD() {
    if (added == true)
        loadedList.delete_new_files();
    char dir[120]; //input dir
    cin >> dir;
    string file_name; //input file name (example.csv)
    cin >> file_name;
    strcat(dir, "/"); //dir + "/"
    strcat(dir, file_name.c_str()); //dir/+example.csv
    if (access(dir, F_OK) == 0) { //if file exist
        string str; //for getline
        ifstream file(dir);
        int cnt = 0;
        //get line by line
        while (getline(file, str)) {
            char ch[str.length()];
            strcpy(ch, str.c_str());
            //seperate by ","
            char *num = strtok(ch, ",");
            //seperate by "."
            char *name = strtok(NULL, ".");
            if (cnt == 0) {//fixing zwnbsp
                cnt++;
                num[0] = num[3];
                num[1] = num[4];
                num[2] = num[5];
                num[3] = '\0';
            }
            loadedList.InsertNode(1, name, num);
        }
        cout << "=======ADD=======" << endl;
        cout << "Success" << endl;
        cout << "==================" << endl;
        added = true; //check added
    } else { //don't exist
        cout << "=======ERROR=======" << endl;
        cout << "200" << endl;
        cout << "==================" << endl;
    }
}
void Manager::MODIFY() {
    string tmp_command;
    //get command 1line
    getline(cin, tmp_command);
    char ch[tmp_command.length()];
    strcpy(ch, tmp_command.c_str());
    //seperate by "\""
    char *dir = strtok(ch, " \"");
    //seperate by "\"";
    char *name = strtok(NULL, "\"");
    //seperate by "\n"
    char *num = strtok(NULL, "\n");
    //delete space
    num[0] = num[1], num[1] = num[2], num[2] = num[3], num[3] = '\0';

    if (dir == NULL) {
        cout << "=======ERROR=======" << endl;
        cout << "300" << endl;
        cout << "==================" << endl;
        return;
    }
    if (name == NULL || num == NULL) {
        cout << "=======ERROR=======" << endl;
        cout << "300" << endl;
        cout << "==================" << endl;
        return;
    }
    bool new_files = false;
    if (strcmp(dir, "img_files") != 0)
        new_files = true;
    if (new_files == false) {
        loadedList.ModifyNode(0, name, num);
    } else {
        loadedList.ModifyNode(1, name, num);
    }
}
void Manager::MOVE() {
    //maximum of linked list is 100
    char dir[15];
    char name[100];
    int num;
    if (loadedList.return_dir() == -1) //if don't exist
    {
        cout << "=======ERROR=======" << endl;
        cout << "400" << endl;
        cout << "==================" << endl;
        return;
    } else {
        for (int i = 0; i < 100; i++) {
            if (loadedList.return_dir() == 0) {
                strcpy(dir, "img_files"); //get dir
                strcpy(name, loadedList.return_name(0)); //get name
                num = loadedList.return_num(0); //get num
                loadedList.delete_tail(0); //delete node which i got info
            } else if (loadedList.return_dir() == 1) {
                strcpy(dir, "new_files");
                strcpy(name, loadedList.return_name(1));
                num = loadedList.return_num(1);
                loadedList.delete_tail(1);
            } else if (loadedList.return_dir() == -1) {
                break;
            }
            databaseBst.Move_Create_BST(dir, name, num);
        }
        cout << "=======MOVE=======" << endl;
        cout << "Success" << endl;
        cout << "==================" << endl;
    }
}
void Manager::PRINT() {
    if (databaseBst.BST_exist() == 1) { //if exist
        databaseBst.print_all();
        cout << "=======PRINT=======" << endl;
        cout << "Success" << endl;
        cout << "==================" << endl;
    } else {
        cout << "=======ERROR=======" << endl;
        cout << "500" << endl;
        cout << "==================" << endl;
    }
}
void Manager::SEARCH() {
    char word[100];
    cin >> word;
    int size = strlen(word);
    //delete "\""
    for (int i = 0; i < size - 1; i++)
        word[i] = word[i + 1];
    //delete "\""
    word[size - 2] = '\0';

    if (databaseBst.BST_exist() == 1) {
        databaseBst.make_queue(); //make queue by post-order style
        databaseBst.search_queue(word); //find word in queue
        cout << "=======SEARCH=======" << endl;
        cout << "Success" << endl;
        cout << "==================" << endl;
    } else {
        cout << "=======ERROR=======" << endl;
        cout << "600" << endl;
        cout << "==================" << endl;
    }
}
void Manager::SELECT() {
    if (databaseBst.BST_exist() == 1) {
        int num;
        cin >> num;
        strcpy(file_name2, databaseBst.select_BST(num)); //get file_name by number
        if (strcmp(file_name2, "\0") != 0) {
            file_num = num; //if find, num = file_num
            strcpy(file_dir, databaseBst.select_BST_dir(num));
            cout << "=======SELECT=======" << endl;
            cout << "Success" << endl;
            cout << "==================" << endl;
        } else { //if not
            cout << "=======ERROR=======" << endl;
            cout << "700" << endl;
            cout << "==================" << endl;
        }
    } else {
        cout << "=======ERROR=======" << endl;
        cout << "700" << endl;
        cout << "==================" << endl;
    }
}

void Manager::EDIT() {
    char command[3];
    cin >> command;
    if (file_num != '\0') {
        //declare FILE input_file, output_file
        FILE *input_file, *output_file;
        //declare input_data 256*256
        unsigned char input_data[256][256];
        char tmp2[100];
        //get dir to get file
        strcpy(tmp2, file_dir);
        strcat(tmp2, "/images/");
        strcat(tmp2, file_name2);
        strcat(tmp2, ".RAW");
        //file open for read
        input_file = fopen(tmp2, "rb");
        if (input_file == NULL) { //if input_file =NULL error
            cout << "=======ERROR=======" << endl;
            cout << "800" << endl;
            cout << "==================" << endl;
            return;
        }
        //set input_data each size 1 for 256*256 from input_file
        fread(input_data, sizeof(unsigned char), 256 * 256, input_file);

        //flipped raw file
        if (strcmp(command, "-f") == 0) {
            unsigned char output_data[256][256];
            //make stack for flip
            Stack_Node *stack_tail = stack_root;
            for (int i = 0; i < 256; i++) {
                for (int j = 0; j < 256; j++) {
                    if (stack_root == NULL) {
                        stack_root = new Stack_Node;
                        stack_root->num = input_data[i][j];
                        stack_tail = stack_root;
                    } else {
                        stack_tail->next = new Stack_Node;
                        stack_tail = stack_tail->next;
                        stack_tail->num = input_data[i][j];
                    }
                }
            }
            //use last input from stack and save data
            for (int i = 0; i < 256; i++) {
                for (int j = 0; j < 256; j++) {
                    Stack_Node *tmp = stack_root;
                    while (tmp->next != stack_tail && tmp != stack_tail) {
                        tmp = tmp->next;
                    }
                    output_data[i][j] = (char) (stack_tail->num);
                    delete stack_tail;
                    stack_tail = tmp;
                }
            }
            //save result flipped
            char result[100] = "Result/";
            strcat(result, file_name2);
            strcat(result, "_flipped.RAW");
            output_file = fopen(result, "w+");
            fwrite(output_data, sizeof(unsigned char), 256 * 256, output_file);
            fclose(input_file);
            fclose(output_file);

        }
            //set bright to raw file.
        else if (strcmp(command, "-l") == 0) {
            unsigned char output_data[256][256];
            //get bright
            int bright = 0;
            cin >> bright;
            cout << bright << endl;
            //make queue for fix bright
            Queue_Node *queue_tail = queue_root;
            for (int i = 0; i < 256; i++) {
                for (int j = 0; j < 256; j++) {
                    if (queue_root == NULL) {
                        queue_root = new Queue_Node;
                        queue_root->num = input_data[i][j];
                        queue_tail = queue_root;
                    } else {
                        queue_tail->next = new Queue_Node;
                        queue_tail = queue_tail->next;
                        queue_tail->num = input_data[i][j];
                    }
                }
            }
            //set oldest queue bright,
            //maximum of bright = 128 because range is -128~127
            for (int i = 0; i < 256; i++) {
                for (int j = 0; j < 256; j++) {
                    Queue_Node *currNode = queue_root;
                    int input_bright = queue_root->num;
                    input_bright+=bright;
                    if(input_bright>255)
                        input_bright=255;
                    output_data[i][j] = input_bright;
                    currNode = currNode->next;
                    delete queue_root;
                    queue_root = currNode;
                }
            }
            //save Result adjusted
            char result[100] = "Result/";
            strcat(result, file_name2);
            strcat(result, "_adjusted.RAW");
            output_file = fopen(result, "w+");
            fwrite(output_data, sizeof(unsigned char), 256 * 256, output_file);
            fclose(input_file);
            fclose(output_file);
        }
            //risized raw file
        else if (strcmp(command, "-r") == 0) {
            //width and height gonna half
            unsigned char output_data[128][128];
            //calculate average from 4 data(square), and set output_data
            for (int i = 0; i < 128; i++) {
                for (int j = 0; j < 128; j++) {
                    int average = 0;
                    average += input_data[2 * i + 1][2 * j + 1];
                    average += input_data[2 * i][2 * j + 1];
                    average += input_data[2 * i + 1][2 * j];
                    average += input_data[2 * i][2 * j];
                    average /= 4;
                    output_data[i][j] = (char) average;
                }
            }
            //save result resized
            char result[100] = "Result/";
            strcat(result, file_name2);
            strcat(result, "_resized.RAW");
            output_file = fopen(result, "w+");
            fwrite(output_data, 1, 128 * 128, output_file);
            fclose(input_file);
            fclose(output_file);
        }
        cout << "=======EDIT=======" << endl;
        cout << "Success" << endl;
        cout << "==================" << endl;
        return;
    } else {
        cout << "=======ERROR=======" << endl;
        cout << "800" << endl;
        cout << "==================" << endl;
        return;
    }
}