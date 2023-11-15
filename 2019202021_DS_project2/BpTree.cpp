#include "BpTree.h"

bool BpTree::Insert(int key, set<string> set) {
    if(root==NULL){//if nothing exist
        auto* Node = new BpTreeDataNode;
        FrequentPatternNode* Frequency = new FrequentPatternNode;
        Frequency->setFrequency(key);
        Frequency->InsertList(set);
        Node->insertDataMap(key,Frequency);
        root = Node;

        return true;
    }
    //get data node by key
    BpTreeNode* currNode = searchDataNode(key);
    //data node is not found and chile is not NULL
    if(currNode==NULL||currNode->getMostLeftChild()!=NULL)
        return false;
    auto curr_data = currNode->getDataMap()->begin();
    int curr_data_size = currNode->getDataMap()->size();
    bool exist= false;
    //search for key
    for(int i=0;i<curr_data_size;i++){
        //key exist
        if(curr_data->first==key){
            exist= true;
            curr_data->second->InsertList(set);
            break;
        }
        curr_data++;
    }
    if(exist== false){//not exist
        //create new node key, insert data to node
        FrequentPatternNode* Frequency = new FrequentPatternNode;
        Frequency->setFrequency(key);
        Frequency->InsertList(set);
        currNode->insertDataMap(key,Frequency);
        if(excessDataNode(currNode)){
            splitDataNode(currNode);//split data node
        }
    }
    return true;
}

BpTreeNode* BpTree::searchDataNode(int n) {//function for search
    BpTreeNode* pCur = root;
    //is child is not exist
    if(pCur->getMostLeftChild()==NULL)
        return root;
    while(1){
        auto curr_data = pCur->getIndexMap()->begin();
        int curr_data_size=pCur->getIndexMap()->size();
        for(int i=0;i<curr_data_size;i++){//set by data node
            if(i==0 & n<curr_data->first)
                pCur=pCur->getMostLeftChild(); //goto most left
            else if(n>=curr_data->first)
                pCur=curr_data->second;//goto next
            curr_data++;
        }
        if(pCur->getMostLeftChild()==NULL)//if curnode's child is null
            break;
    }
    return pCur;
}

void BpTree::splitDataNode(BpTreeNode* pDataNode) {//split data node function

    int num = ceil((order-1)/2.0)+1; //location of data node

    auto* last_data = new BpTreeDataNode;

    auto curr_data = pDataNode->getDataMap()->rbegin();
    int curr_data_size = pDataNode->getDataMap()->size();
    //split datanode
    for(int i=curr_data_size;i>num-1;i--){
        last_data->insertDataMap(curr_data->first,curr_data->second);
        curr_data++;
    }
    curr_data--;
    auto tmp = curr_data->first;
//split datanode
    for(int i=curr_data_size;i>num-1;i--){
        curr_data = pDataNode->getDataMap()->rbegin();
        pDataNode->deleteMap(curr_data->first);
    }
//setting last datanode
    last_data->setPrev(pDataNode);
    last_data->setNext(pDataNode->getNext());
//if datanode exist
    if(pDataNode->getNext()!=NULL){
        pDataNode->getNext()->setPrev(last_data);
    }
    pDataNode->setNext(last_data);
//if exist
    if(pDataNode->getParent()!=NULL){
        auto* Node=pDataNode->getParent();
        //set first datanode and last node
        Node->insertIndexMap(tmp,last_data);
        last_data->setParent(Node);
        //split index node
        if(excessIndexNode(Node))
            splitIndexNode(Node);
    }
    else{
        //craete new node and set parent child and left
        auto* Node = new BpTreeIndexNode;
        last_data->setParent(Node);
        pDataNode->setParent(Node);

        Node->setMostLeftChild(pDataNode);
        Node->insertIndexMap(tmp,last_data);
        if(pDataNode==root)
            root=Node;//change root
    }

}

void BpTree::splitIndexNode(BpTreeNode* pIndexNode) {//functino for split index node
    int num=ceil((order-1)/2.0)+1;//calculate for split index
    //create last indexnode
    auto* last_node = new BpTreeIndexNode;
    auto curr_data=pIndexNode->getIndexMap()->rbegin();
    int curr_data_size = pIndexNode->getIndexMap()->size();
//goto lear node
    for(int i=curr_data_size;i>num;i--){
        last_node->insertIndexMap(curr_data->first,curr_data->second);
        curr_data++;
    }
    int tmp1=curr_data->first;
    auto tmp2=curr_data->second;
//split first and last
    for(int i = curr_data_size;i>num-1;i--){
        curr_data=pIndexNode->getIndexMap()->rbegin();
        pIndexNode->deleteMap(curr_data->first);
    }
//set parent
    tmp2->setParent(last_node);
    curr_data = last_node->getIndexMap()->rbegin();
    curr_data_size = last_node->getIndexMap()->size();
    for(int i=0;i<curr_data_size;i++){
        curr_data->second->setParent(last_node);
    }
    if(pIndexNode->getParent()!=NULL){//if exist
        //insert node and set parent child and left
        auto* Node = pIndexNode->getParent();
        Node->insertIndexMap(tmp1,last_node);
        last_node->setParent(Node);
        last_node->setMostLeftChild(tmp2);
        //larger than bporder
        if(excessIndexNode(Node))
            splitIndexNode(Node);//split
    }
    else{ //if not exist
        //create center node
        auto* prevNode = new BpTreeIndexNode;
        prevNode->insertIndexMap(tmp1,last_node);
        prevNode->setMostLeftChild(pIndexNode);
        pIndexNode->setParent(prevNode);
        last_node->setParent(prevNode);
        last_node->setMostLeftChild(tmp2);
        if(pIndexNode==root)
            root=prevNode;//change root
    }

}
//return overflow in datanode
bool BpTree::excessDataNode(BpTreeNode* pDataNode) {
    if (pDataNode->getDataMap()->size() > order - 1) return true;//order is equal to the number of elements
    else return false;
}
//return overflow in indexnode
bool BpTree::excessIndexNode(BpTreeNode* pIndexNode) {
    if (pIndexNode->getIndexMap()->size() > order - 1)return true;//order is equal to the number of elements
    else return false;
}

//print confidence
bool BpTree::printConfidence(string item, double item_frequency, double min_confidence)
{
    int min_num = ceil(item_frequency*min_confidence);//calculate min
    BpTreeNode* currNode = searchDataNode(min_num);//set currnode

    bool check = false;
    while(currNode != NULL){
        auto data = currNode->getDataMap()->begin();
        int size = currNode->getDataMap()->size();
        for(int i=0;i<size;i++){
            if(data->first>=min_num){
                FrequentPatternNode* second = data->second;
                //access set and in pattern
                for(auto tmp1:second->getList()){
                    for(auto tmp2:tmp1.second){//access string of set
                        if(tmp2==item){//if equal
                            check = true;
                            break;
                        }
                    }
                    if(check == true)
                        break;
                }
                if(check== true)
                    break;
            }
            data++;
        }
        if(check== true)
            break;
        currNode=currNode->getNext();
    }
    if(check== false)
        return false;
    *fout << "FrequentPattern Frequency Confidence" <<endl;
    while(currNode!=NULL){
        auto data =currNode->getDataMap()->begin();
        int size = currNode->getDataMap()->size();
        for(int i=0;i<size;i++){//access frequency and pattern
            if(data->first>=min_num){//if bigger
                FrequentPatternNode* second = data->second;
                for(auto tmp1:second->getList()){
                    for(auto tmp2: tmp1.second){//access string in set
                        if(tmp2==item){//print
                            printFrequentPatterns(tmp1.second,tmp2);
                            double per = ((double)data->first/min_confidence);
                            *fout<<fixed;
                            fout->precision(2);
                            *fout<<" "<<data->first<<" "<<per <<endl;
                        }
                    }
                }
            }
            data++;
        }
        currNode=currNode->getNext();
    }
    return true;
}
bool BpTree::printFrequency(string item, int min_frequency)//print winratio in ascending order
{
    //set currnode to get datanode
    BpTreeNode* currNode = searchDataNode(min_frequency);
    bool check = false;
    while(currNode!=NULL){
        auto data = currNode->getDataMap()->begin();
        int size = currNode->getDataMap()->size();
        for(int i =0;i<size;i++){
            if(data->first>=min_frequency){
                FrequentPatternNode* second = data->second;
                for(auto tmp1:second->getList()){//access set and pattern
                    for(auto tmp2: tmp1.second){//access string in set
                        if(tmp2==item){//if equal
                            check = true;
                            break;
                        }
                    }
                    if(check == true)
                        break;
                }
                if(check== true)
                    break;
            }
            data++;
        }
        if(check== true)
            break;
        currNode=currNode->getNext();
    }
    if(check== false)
        return false;
    *fout << "FrequentPattern Frequency"<<endl;
    while(currNode!=NULL){//access to data node
        auto data = currNode->getDataMap()->begin();
        int size = currNode->getDataMap()->size();
        //access frequency and pattern
        for(int i=0;i<size;i++){
            if(data->first>=min_frequency){
                FrequentPatternNode* second = data->second;
                for(auto tmp1:second->getList()){//access set and pattern
                    for(auto tmp2:tmp1.second){//access string
                        if(tmp2==item){//if equal, print
                            printFrequentPatterns(tmp1.second,tmp2);
                            *fout <<data->first<<endl;
                        }
                    }
                }
            }
            data++;
        }
        currNode=currNode->getNext();
    }
    return true;
}
bool BpTree::printRange(string item, int min, int max) {
    //set currnode to get data node
    BpTreeNode* currNode = searchDataNode(min);
    //if next node is null
    if(currNode->getNext()==NULL){
        auto tmp_cur = currNode->getDataMap()->rbegin();
        if(tmp_cur->first<min)
            return false;
    }
    bool check = false;
    while(currNode!=NULL){
        auto data = currNode->getDataMap()->begin();
        int size = currNode->getDataMap()->size();
        for(int i=0;i<size;i++){
            if(data->first>=min && data->first<=max){
                FrequentPatternNode* second = data->second;
                for(auto tmp1:second->getList()){//access set and pattern
                    for(auto tmp2:tmp1.second){//access string
                        if(tmp2==item){
                            check = true;
                            break;
                        }
                    }
                    if(check == true)
                        break;
                }
                if(check== true)
                    break;
            }
            data++;
        }
        if(check == true)
            break;
        currNode=currNode->getNext();
    }
    if(check== false)
        return false;
    *fout <<"FrequentPattern Frequency"<<endl;
    //access to data node
    while(currNode!=NULL){
        auto data = currNode->getDataMap()->begin();
        int size = currNode->getDataMap()->size();
        for(int i=0;i<size;i++){//access ffrequency and pattern
            if(data->first>=min&&data->first<=max){
                FrequentPatternNode* second = data->second;
                for(auto tmp1:second->getList()){//access set and pattern
                    for(auto tmp2:tmp1.second){//access string
                        if(tmp2==item){//if equal, print
                            printFrequentPatterns(tmp1.second,tmp2);
                            *fout<<data->first<<endl;
                        }
                    }
                }
            }
            data++;
        }
        currNode=currNode->getNext();
    }
    return true;
}
//print frequentPattern function
void BpTree::printFrequentPatterns(set<string> pFrequentPattern, string item) {
    *fout << "{";
    set<string> curPattern = pFrequentPattern;
    curPattern.erase(item);
    for (set<string>::iterator it = curPattern.begin(); it != curPattern.end();) {
        string temp = *it++;
        if (temp != item) *fout << temp;
        if (it == curPattern.end()) {
            *fout << "} ";
            break;
        }
        *fout << ", ";
    }
}
