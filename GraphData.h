#ifndef GRAPHDATA_H
#define GRAPHDATA_H

#include <vector>
#include "Graph.h"
using namespace std;

class GraphData {

public:
	vector<int> newId;//为reLabel后的节点赋予新的id
	vector<int> vertexLabel;//节点标签
	vector<bool> vertexMask;//节点掩码
	vector<int> from;//边的from顶点
	vector<int> to;//边的to顶点
	vector<int> edgeLabel;//边标签
	vector<bool> edgeMask;//边掩码

	Graph& buildGraph(Graph &g);
};
#endif
