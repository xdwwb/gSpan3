#include "EdgeFrequency.h"
EdgeFrequency ef;

int &EdgeFrequency::operator()(int fromLabel, int eLabel, int toLabel){
    return dynamicArray[fromLabel*y*z+eLabel*z+toLabel];
}
void EdgeFrequency::init(int node_label_size, int edge_label_size, int _min_sup){
    min_sup=_min_sup;
    x=node_label_size;
    y=edge_label_size;
    z=node_label_size;
    dynamicArray=new int[x*y*z];
}

