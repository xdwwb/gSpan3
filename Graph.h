/**
 * Project gSpan
 * @author wwb
 * @version 0.1
 */


#ifndef _GRAPH_H
#define _GRAPH_H
#include<vector>
#include<iostream>

using namespace std;

class Graph {
public: 
	vector<int>vertexLabel;
	vector<vector<int>>edgeTo;
	vector<vector<int>>edgeLabel;

	//vector<int>supporter;

    void addVertex(int eLabel);
    void addEdge(int from ,int to, int eLabel);
    void show();
    bool hasEdge(int fromLabel,int eLabel,int toLabel);//end hasEdge

    void removeEdge(int fromLabel,int eLabel,int toLabel);
};//end class

#endif //_GRAPH_H
