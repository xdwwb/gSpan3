#ifndef FSGRAPH_H
#define FSGRAPH_H
#include "Graph.h"
#include "DFScode.h"
#include <vector>
using namespace std;

class FSGraph{
public:
	Graph g;
	DFScode gc;
	vector<int> supporter;
    void show();
	void saveToFile(){
	
	}
};

#endif
