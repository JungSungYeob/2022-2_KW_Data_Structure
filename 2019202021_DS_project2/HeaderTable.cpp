#include "HeaderTable.h"

HeaderTable::~HeaderTable() {//destructor

}

void HeaderTable::insertTable(char *item, int frequency) {
    string str1(item);
    //search for data
    for (pair<int, string> &data: indexTable) {
        string str2 = data.second;
        if (str1 == str2) {//if same get frequency
            data.first = data.first + frequency;
            descendingIndexTable();
            return;
        }
    }
    //insert new item  with frequency and str1
    indexTable.push_back(make_pair(frequency, str1));
    //insert new FPNode and next to fpnode
    dataTable.insert(make_pair(item, new FPNode));
    descendingIndexTable();//descending sort
    return;
}

int HeaderTable::find_frequency(string item) {
    int frequency = 0;//set frequency
    string str1=item;
    //access frequency data and item data
    for(pair<int,string> data: indexTable){
        string str2 =data.second;
        if(str1==str2){//if same get frequency about data's first
            frequency=data.first;
        }
    }
    return frequency;
}
