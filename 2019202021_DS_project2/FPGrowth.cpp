#include "FPGrowth.h"


FPGrowth::~FPGrowth() {

}

void FPGrowth::createFPtree(FPNode* root, HeaderTable* table, list<string> item_array, int frequency) {
    FPNode* currNode=root;//get currNode
    //save item of item table
    list<pair<int,string>> item_list;
    //access indextable
    for(auto data1: table->getindexTable()){
        //access string int datatable
        for(auto data2: item_array){
            //if second is same and frequency bigger than threshhold
            if(data1.second==data2&&table->find_frequency(data2)>=threshold){
                item_list.push_back(make_pair(1,data2));
            }
        }
    }
    //if root == NULL
    if(root->getChildren().size()==0){
        for(auto data1: item_list){
            FPNode * Node = new FPNode;
            currNode->pushchildren(data1.second,Node);
            Node->setParent(currNode);
            Node->updateFrequency(1);
            Node->setitem((char*)data1.second.c_str());
            connectNode(table,data1.second,Node);
            currNode=currNode->getChildrenNode(data1.second);
        }
    }
        //if root != NULL
    else
        //goto string item itemtable
        for(auto& item: item_list){
            //goto child
            for(auto& child:currNode->getChildren()){
                //if exist
                if(child.first==item.second&&item.first==1){
                    //get old node to update
                    item.first=0;
                    child.second->updateFrequency(1);
                    currNode=child.second;
                }
            }
            //if child not exist create new node
            if(item.first==1){
                item.first=0;
                //create new
                FPNode*Node=new FPNode;
                currNode->pushchildren(item.second,Node);
                //set node
                Node->setParent(currNode);
                Node->updateFrequency(1);
                Node->setitem((char*)item.second.c_str());
                //connect old node to new
                connectNode(this->table,item.second,Node);
                currNode=currNode->getChildrenNode(item.second);
            }
        }
}
//function for connect
void FPGrowth::connectNode(HeaderTable* table, string item, FPNode* node) {
    FPNode* currNode =NULL;
    //goto node pointer
    for(auto data1:table->getdataTable()){
        if(data1.first==item){//if find
            currNode=data1.second;
            //if address is not exist
            if(currNode->getNext()==NULL){
                currNode->setNext(node);//connect
            }
            else{//if exist
                currNode=currNode->getNext();
                //goto last node
                while(currNode->getNext()!=NULL){
                    currNode=currNode->getNext();
                }
                //connect
                currNode->setNext(node);
            }
        }
    }
}

//save
bool FPGrowth::contains_single_path(FPNode* pNode) {
    if (pNode->getChildren().size() == 0) return true;
    else if (pNode->getChildren().size() > 1) return false;
    return contains_single_path(pNode->getChildren().begin()->second);
}

map<set<string>, int> FPGrowth::getFrequentPatterns(HeaderTable* pTable, FPNode* pTree) {

    return {};
}



void FPGrowth::powerSet(map<set<string>, int>* FrequentPattern, vector<string> data, string item, int frequency, int* ptr, int depth) {
    if (data.size() == depth) {
        set<string> set; set.insert(item);
        for (int i = 0; i < data.size(); i++) { if (ptr[i] == 1) set.insert(data[i]); }
        FrequentPattern->insert(make_pair(set, frequency)); return;
    }
    ptr[depth] = 1;
    powerSet(FrequentPattern, data, item, frequency, ptr, depth + 1);
    ptr[depth] = 0;
    powerSet(FrequentPattern, data, item, frequency, ptr, depth + 1);
}
//end
//print
bool FPGrowth::printList() {
    //get index table
    auto index_table=table->getindexTable();
    if(index_table.empty())//if empty
        return false;
    //(individual memo)if error occur, change flog to fout*
    *fout << "Item\tFrequency"<<endl;
    for(pair<int,string>data1:index_table){
        (*fout)<<data1.second<<"\t"<<data1.first<<endl;
    }
    return true;
}
bool FPGrowth::printTree() {

    //set node
    FPNode * currNode =NULL;
    FPNode * tmpNode = NULL;
    //if empty
    if(fpTree->getChildren().empty())
        return false;
    //set ascendingindex
    getHeaderTable()->ascendingIndexTable();
    *fout<<"{StandardItem,Frequency} (Path_Item,Frequency)"<<endl;
    //goto indextable
    for(auto data1:getHeaderTable()->getindexTable()){
        //frequency in index data bigger than threshold print
        if(data1.first>=threshold){
            *fout<<"{"<<data1.second<<","<<data1.first<<"}"<<endl;
            //goto pointer data in table
            for(auto data2:getHeaderTable()->getdataTable()){
                //if equal
                if(data1.second==data2.first){
                    currNode=data2.second->getNext();
                    while(currNode!=NULL){//access the parent of node
                        tmpNode=currNode;
                        while(tmpNode!=fpTree){//print node data
                            *fout << "(" <<tmpNode->get_Item()<<","<<tmpNode->getFrequency()<<")";
                            tmpNode=tmpNode->getParent();
                        }
                        *fout<<endl;
                        currNode=currNode->getNext();
                    }
                }
            }
        }
    }
    return true;
}
//plus score
void FPGrowth::saveFrequentPatterns(){
    //try after bptree
}
