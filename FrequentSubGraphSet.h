#ifndef FREQUENTSUBGRAPHSET_H
#define FREQUENTSUBGRAPHSET_H

#include "FSGraph.h"
#include <vector>
#include <iostream>
using namespace std;

class FrequentSubGraphSet:public vector<FSGraph>{
public:
    void show();

};

#endif
