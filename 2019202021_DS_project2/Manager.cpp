#include "Manager.h"

void Manager::run(const char *command) {
    char input[255];//command txt
    fin.open(command);//file open
    if (!fin) {//if error (!exist)
        flog << "File Open Error" << endl;
        return;
    }
    while (!fin.eof()) {
        fin.getline(input, 255); //get line by line
        char *tmp = strtok(input, " "); //cut by " "
        if (tmp == NULL)//if !exist
            continue;
        if (strcmp(tmp, "LOAD") == 0) {//command for Load
            flog << "========LOAD========"<<endl;
            if (LOAD()) //if return true
                printSuccessCode();
            else
                printErrorCode(100);
        }
        if (strcmp(tmp, "BTLOAD") == 0) {//command for BTLOAD
            flog << "========BTLOAD========"<<endl;
            if (BTLOAD())//if return true
                printSuccessCode();
            else
                printErrorCode(200);
        }
        if (strcmp(tmp, "PRINT_ITEMLIST") == 0) {//command for PRINT_ITEMLIST
            flog << "========PRINT_ITEMLIST========"<<endl;
            if (PRINT_ITEMLIST())//if return true;
                printSuccessCode();
            else
                printErrorCode(300);
        }
        if (strcmp(tmp, "PRINT_FPTREE") == 0) {//commnad for PRINT_FPTREE
            flog << "========PRINT_FPTREE========"<<endl;
            if (PRINT_FPTREE())//if return true;
                printSuccessCode();
            else
                printErrorCode(400);
        }
        if (strcmp(tmp, "PRINT_BPTREE") == 0) {//command for PRINT_BPTREE
            flog <<"========PRINT_BPTREE========"<<endl;
            bool check = true; //check for true false
            char* tmp1 = strtok(NULL,"  ");//cut by" " for item
            char* tmp2 = strtok(NULL, " ");//cut by " " for min
            if(tmp1==NULL||tmp2==NULL)//if tmp1 or tmp2 is NULL
                check = false;
            if(tmp1!=NULL&&tmp2!=NULL){//if tmp1 and 2 is not NULL
                string tmp_str1(tmp1);
                string tmp_str2(tmp2);
                //if item have space
                while(atoi(tmp2)==0){
                    tmp_str2=tmp2;
                    tmp_str1=tmp_str1+string("  ")+tmp_str2;
                    tmp1 = (char*)tmp_str1.c_str();
                    tmp2 = strtok(NULL, "   ");
                    if(tmp2 == NULL)
                        break;
                }
            }
            else
                check= false;
            //get string
            char* tmp3 = strtok(NULL,"  ");//cut by " "
            if(check== false){//if check is false, print error
                printErrorCode(500);
            }
            else if(tmp1 !=NULL && atoi(tmp2)!=0 && tmp3==NULL){
                if(PRINT_BPTREE(tmp1,atoi(tmp2))){//if all of condition match
                    printSuccessCode();
                }
                else{
                    printErrorCode(500);
                }
            }
            else{
                printErrorCode(500);
            }

        }
        if (strcmp(tmp, "PRINT_CONFIDENCE") == 0) {//command for PRINT_CONFIDENCE
            flog<<"========PRINT_CONFIDENCE========"<<endl;
            bool check = true;//check for true false
            //cut by " " for item and relation
            auto tmp1 = strtok(NULL,"   ");
            auto tmp2 = strtok(NULL, "  ");

            if(tmp1==NULL||tmp2==NULL)//tmp1 or tmp2 is NULL
                check = false;
            if(tmp1!=NULL &&tmp2!=NULL){
                string tmp_str1(tmp1);
                string tmp_str2(tmp2);
                while(atof(tmp2)==0){//if item have space
                    tmp_str2 = tmp2;
                    tmp_str1=tmp_str1+string(" ")+tmp_str2;
                    tmp1 = (char*)tmp_str1.c_str();
                    tmp2 = strtok(NULL, "   ");
                    if(tmp2==NULL)
                        break;
                }
            }
            else
                check = false;
            auto tmp3 = strtok(NULL,"   "); //cut by " "
            if(check == false){
                printErrorCode(600);
            }
            else if(tmp1 != NULL && atof(tmp2)!=0.0 &&tmp3 ==NULL){
                if(PRINT_CONFIDENCE(tmp1,atof(tmp2))){// if all of condition match
                    printSuccessCode();
                }
                else{
                    printErrorCode(600);
                }
            }
            else{
                printErrorCode(600);
            }
        }
        if (strcmp(tmp, "PRINT_RANGE") == 0) {//command for PRINT_RANGE
            flog<<"========PRINT_RANGE========"<<endl;
            bool check = true;//check for true false
            //cut by " " for item and min
            char*tmp1= strtok(NULL,"    ");
            char*tmp2= strtok(NULL,"    ");
            if(tmp1!=NULL &&tmp2!=NULL){
                string tmp_str1(tmp1);
                string tmp_str2(tmp2);
                while(atof(tmp2)==0){//if item have space
                    tmp_str2 = tmp2;
                    tmp_str1=tmp_str1+string("  ")+tmp_str2;
                    tmp1 = (char*)tmp_str1.c_str();
                    tmp2 = strtok(NULL, "   ");
                    if(tmp2==NULL)
                        break;
                }
            }
            else
                check = false;
            //cut by " " for max and string
            char*tmp3= strtok(NULL,"    ");
            char*tmp4= strtok(NULL,"    ");
            if(tmp1==NULL||tmp2==NULL||tmp2==NULL)//one of tmp1 tmp2 tmp3 is null
                check = false;
            if(check== false){
                printErrorCode(700);
            }
            else if(tmp1 !=NULL&&atoi(tmp2)!=0&&atoi(tmp3)!=0&&tmp4==NULL){
                if(PRINT_RANGE(tmp1,atoi(tmp2),atoi(tmp3))){//if all of condition match
                    printSuccessCode();
                }
                else{
                    printErrorCode(700);
                }
            }
            else
                printErrorCode(700);
        }
        if (strcmp(tmp, "SAVE") == 0) {//save for frequency pattern
            flog << "========SAVE========" << endl;
            if (SAVE())
                printSuccessCode();
            else
                printErrorCode(800);
        }
        if (strcmp(tmp, "EXIT") == 0) {//commnad for EXIT
            flog << "========EXIT========" << endl;
            flog << "Success" << endl;
            flog << "====================" << endl;
            return;
        }
    }
    fin.close();
    return;
}

bool Manager::LOAD() {
    //open file
    ifstream market;
    market.open("market.txt");
    //if not exist
    if (!market) {
        return false;
    }
    //if exist headertable empty
    if(!(fpgrowth->getHeaderTable()->getindexTable().empty())) {
        return false;
    }
    char command[2000];
    char *tmp = NULL;
    //if exist get line by line
    while(!market.eof()){
        market.getline(command,2000);
        tmp = strtok(command,"\t");
        if(tmp == NULL)
            continue;
        while(tmp!=NULL){
            fpgrowth->createTable(tmp,1);
            tmp=strtok(NULL,"\t");
        }
    }
    market.close();//close file
    //open new file
    market.open("market.txt");
    tmp=NULL;
    list<string> array;
    //if file exist get line by line
    while(!market.eof()){
        //cut by tab
        market.getline(command,2000);
        tmp = strtok(command,"  ");
        if(tmp == NULL)
            continue;
        //if end
        while(tmp!=NULL){
            string str(tmp);
            array.push_back(str);
            //cut by tab
            tmp=strtok(NULL,"   ");
        }
        //create FPtreeitem
        fpgrowth->createFPtree(fpgrowth->getTree(),fpgrowth->getHeaderTable(),array,1);
        //clear array
        array.clear();
    }

    return true;
}


bool Manager::BTLOAD() {
    //open result file
    ifstream result;
    result.open("result.txt");
    //if not exist
    if(!result)
        return false;
    //if bptree exist
    if(bptree->getRoot()!=NULL)
        return false;
    char command[2000];
    char* tmp = NULL;
    set<string> set;
    //if result exist get line by line
    while(!result.eof()){
        result.getline(command,2000);
        //cut by tab
        tmp = strtok(command,"  ");
        if(tmp==NULL)
            continue;
        int num = 0;
        //continue until end
        while(tmp !=NULL){
            if(atoi(tmp)!=0){
                num = atoi(tmp);
            }
            else
                set.insert(tmp);
            //cut by tab
            tmp=strtok(NULL,"   ");
        }
        if(bptree->Insert(num,set)== false)
            return false;
        set.clear();//clear set
    }
    result.close();//close file
    return true;
}

bool Manager::PRINT_ITEMLIST() {//print itemlist
    return fpgrowth->printList();
}

bool Manager::PRINT_FPTREE() {//print fptree
    return fpgrowth->printTree();
}

bool Manager::PRINT_BPTREE(char *item, int min_frequency) {
    //if not exist bptree is not exist
    if(bptree->getRoot()==NULL)
        return false;
    string tmp(item);
    //if exist print frequency
    return bptree->printFrequency(tmp,min_frequency);
}

bool Manager::PRINT_CONFIDENCE(char *item, double rate) {
    //if return false
    if(bptree->getRoot()==NULL)
        return false;
    //if percentage of rate is bigger than 1
    if(rate>=1)
        return false;
    string tmp(item);
    //if exist item
    int num =0;
    for(auto tmp1:fpgrowth->getHeaderTable()->getindexTable()){
        if(tmp1.second==tmp){
            num=tmp1.first;
            break;
        }
    }
    if(num==0)
        return false;
    //call printconfidence
    return bptree->printConfidence(tmp,rate,num);
}

bool Manager::PRINT_RANGE(char *item, int start, int end) {
    //if bptree not exist
    if(bptree->getRoot()==NULL)
        return false;
    string tmp(item);
    //if exist, print bptree's range
    return bptree->printRange(tmp,start,end);
}

bool Manager::SAVE() {
    if(fpgrowth->getHeaderTable()->getindexTable().empty())
        return false;
    fpgrowth->saveFrequentPatterns();
}

void Manager::printErrorCode(int n) {                //ERROR CODE PRINT
    flog << n << endl;
    flog << "=======================" << endl << endl;
}

void Manager::printSuccessCode() {//SUCCESS CODE PRINT
    flog << "Success" << endl;
    flog << "=======================" << endl << endl;
}
