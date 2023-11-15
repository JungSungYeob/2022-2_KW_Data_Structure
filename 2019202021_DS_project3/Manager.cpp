//
// Created by 정성엽 on 2022/12/10.
//
#include "Manager.h"

Manager::Manager() {
    //constructor
    graph = nullptr;
    fout.open("log.txt", ios::app);
    load = 0;
}

Manager::~Manager() {
    //destructor
    if (load)
        delete graph;
    fout.close();
}

void Manager::run(const char *command_txt) {
    ifstream fin;
    fin.open(command_txt);
    //run by command

    if (!fin) {
        fout << "[ERROR] command file open error!" << endl;
        return;
    }
    char *str;
    char *str2;
    char buf[129] = {0};

    while (fin.getline(buf, 128)) {//get command
        str = strtok(buf, " ");
        str2 = strtok(NULL, " ");
        if (str == NULL && str2 == NULL)continue;

        //command EXIT
        if (strcmp(str, "EXIT") == 0) {
            break;
            //command LOAD
        } else if (strcmp(str, "LOAD") == 0) {
            if (str2 == NULL) {//if str2 == NULL
                printErrorCode(100);
                continue;
            }
            if (LOAD(str2)) {
                fout << "==========LOAD==========" << endl;
                fout << "Success" << endl;
                fout << "========================" << endl;
            } else {
                printErrorCode(100);
                continue;
            }
        }
            //command PRINT
        else if (strcmp(str, "PRINT") == 0) {
            if (load != true) {
                printErrorCode(200);
                continue;
            }
            if (graph != nullptr) {//if graph is not exist
                PRINT();
            } else {
                printErrorCode(200);
                continue;
            }
        }
            //command BFS
        else if (strcmp(str, "BFS") == 0) {
            if (load != true) {
                printErrorCode(300);
                continue;
            }
            if (str2 == NULL) {//if str2==NULL
                printErrorCode(300);
                continue;
            }
            if (mBFS(stoi(str2))) {//start BFS with str2 which convert to integer

            } else {
                printErrorCode(300);
                continue;
            }
        } else if (strcmp(str, "DFS") == 0) {
            if (load != true) {
                printErrorCode(400);
                continue;
            }
            if (str2 == NULL) {//if str2==NULL
                printErrorCode(400);
                continue;
            }
            if (mDFS(stoi(str2))) {//start DFS with str2 which convert to integer

            } else {
                printErrorCode(400);
                continue;
            }
        } else if (strcmp(str, "DFS_R") == 0) {
            if (load != true) {
                printErrorCode(500);
                continue;
            }
            if (str2 == NULL) {//if str2==NULL
                printErrorCode(500);
                continue;
            }
            if (mDFS_R(stoi(str2))) {//start DFS_R with str2 which convert to integer

            } else {
                printErrorCode(500);
                continue;
            }
        } else if (strcmp(str, "KRUSKAL") == 0) {
            if (load != true) {
                printErrorCode(600);
                continue;
            }
            if (mKRUSKAL()) {

            } else {
                printErrorCode(600);
                continue;
            }
        } else if (strcmp(str, "DIJKSTRA") == 0) {
            if (load != true) {
                printErrorCode(700);
                continue;
            }
            if (str2 == NULL) {//if str2==NULL
                printErrorCode(700);
                continue;
            }
            if (mDIJKSTRA(stoi(str2))) {//start DIJKSTRA with str2 which convert to integer

            } else {
                printErrorCode(700);
                continue;
            }
        } else if (strcmp(str, "BELLMANFORD") == 0) {
            if (load != true) {
                printErrorCode(800);
                continue;
            }
            char *str3;//end vertex
            str3 = strtok(NULL, " ");
            if (str2 == NULL || str3 == NULL) {//if str2 or str3==NULL
                printErrorCode(800);
                continue;
            }
            if (mBELLMANFORD(stoi(str2), stoi(str3))) {//start BELLMANFORD with str2, str3 which convert to integer

            } else {
                printErrorCode(800);
                continue;
            }

        } else if (strcmp(str, "FLOYD") == 0) {
            if (load != true) {
                printErrorCode(900);
                continue;
            }
            if (mFLOYD()) {

            } else {
                printErrorCode(900);
            }
        }


    }
    fin.close();
}

bool Manager::LOAD(char *filename) {
    ifstream fin2;
    fin2.open(filename);//file open graph
    if (!fin2) {
        return false;
    }
    if (load = true)//if graph is already exist, delete previous graph
        delete graph;
    load = true;//if file exist
    char cmd_fin2[1024];
    char graph_type;
    int graph_size;
    fin2.getline(cmd_fin2, 1024);
    graph_type = cmd_fin2[0];
    fin2.getline(cmd_fin2, 1024);
    graph_size = stoi(cmd_fin2);

    if (graph_type == 'L') {
        //cout << "List" << endl;
        int i = 0;
        graph = new ListGraph(0, graph_size);//generate new
        while (!fin2.eof()) {
            fin2.getline(cmd_fin2, 1024);//get information of file
            char *tmp1, *tmp2;
            tmp1 = strtok(cmd_fin2, " ");//get first number
            tmp2 = strtok(NULL, "");//get second number
            //if tmp2==NULL => vertex
            if (tmp2 == NULL) {
		if(tmp1==NULL)
			continue;
                i = atoi(tmp1);//if second number is NULL, first number is vertex
            } else {
                graph->insertEdge(i, stoi(tmp1), stoi(tmp2));//insert edge with weight
            }
        }
    } else if (graph_type == 'M') {
        //cout << "Matrix" << endl;
        graph = new MatrixGraph(1, graph_size);//generate new
        int i = 0;
        while (!fin2.eof()) {
            fin2.getline(cmd_fin2, 1024);
            char *tmp;
            tmp = strtok(cmd_fin2, " ");//get weight
	    if(tmp==NULL)
		continue;
            graph->insertEdge(i, 0, stoi(tmp));//insert edge with weight
            for (int j = 1; j < graph_size; j++) {
                tmp = strtok(NULL, " ");
                graph->insertEdge(i, j, stoi(tmp));
            }
            i++;
        }
    } else {
        return false;
    }

    return true;
}

bool Manager::PRINT() {//execute PRINT
    if (graph->printGraph())
        return true;
    return false;
}

bool Manager::mBFS(int vertex) {//execute BFS
    if (BFS(graph, vertex))
        return true;
    return false;
}

bool Manager::mDFS(int vertex) {//execute DFS
    if (DFS(graph, vertex))
        return true;
    return false;
}


bool Manager::mDFS_R(int vertex) {//execute DFS recursive
    vector<bool> visited(graph->getSize());
    if (DFS_R(graph, visited, vertex))
        return true;
    return false;
}

bool Manager::mDIJKSTRA(int vertex) {//execute dijkstra
    if (Dijkstra(graph, vertex))
        return true;
    return false;
}

bool Manager::mKRUSKAL() {//execute kruskal
    if (Kruskal(graph))
        return true;
    return false;
}

bool Manager::mBELLMANFORD(int s_vertex, int e_vertex) {//execute Bellman-ford
    if (Bellmanford(graph, s_vertex, e_vertex))
        return true;
    return false;
}

bool Manager::mFLOYD() {//execute FLOYD
    if (FLOYD(graph))
        return true;
    return false;
}

void Manager::printErrorCode(int n) {//function for print error
    fout << "======== ERROR ========" << endl;
    fout << n << endl;
    fout << "=======================" << endl;
}
