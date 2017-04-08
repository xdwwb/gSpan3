#ifndef CHILDREN_H
#define CHILDREN_H

#include <vector>
#include "Edge5.h"
#include "Graph.h"
#include "DFScode.h"
#include "assert.h"
#include <set>
#include "EdgeFrequency.h"

using namespace std;

class Children:public set<Edge5>{
public:
	Graph &g;
	DFScode &gc;

	Children(Graph &_g,DFScode &_gc):g(_g),gc(_gc){

	}

    void getChildren();

    void DFS(int current);

private:
	vector<int> graph2code;
	vector<int> code2graph;
	vector<vector<bool>> edgeVisited;
	vector<int> rmPath;
	
};

#endif
