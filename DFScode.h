#ifndef DFSCODE_H
#define DFSCODE_H

#include<vector>
#include"Edge5.h"
#include"Graph.h"
#include"assert.h"

using namespace std;

class DFScode:public vector<Edge5>{
public:
	//vector<int>supporter;//支持者
	//Graph g;//可以保持一致性

	DFScode(){
	}

	DFScode(const DFScode &parent){
		for(size_t i=0;i<parent.size();i++){
			this->push_back(parent[i]);
		}
	}

    Graph& toGraph(Graph& g);

	//多写几个，想怎么用就怎么用！

    bool isMin(Graph &g);

    bool isMin(const Graph& g,const DFScode &gc);

    void show();

private:
	//所需要的局部变量
	bool is_min;
	vector<int> *pgraph2code;
	vector<vector<bool>> *pedgeVisited;
	
    void DFS(const Graph& g,vector<int>& v,int current,int next);

};

#endif
