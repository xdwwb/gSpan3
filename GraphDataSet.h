#ifndef GRAPHDATASET_H
#define GRAPHDATASET_H
#include <vector>
#include <iostream>
#include "GraphData.h"
#include <fstream>
using namespace std;

class GraphDataSet:public vector<GraphData>{
public:

	int vertex_label_size;
	int edge_label_size;

	//从文件读取数据
	void readFromFile(ifstream &in);
	void reLabel(double min_sup_rate);

	
private:
	//用于统计频率
	int min_sup;
	vector<int>eLabels;
	vector<int>vLabels;
	class LabelInfo{
	public:
		int label;
		int frequency;
		int order;
		bool mask;
		
        LabelInfo(int l,int f,int o);
        bool operator<(LabelInfo &b);
        static bool compareByLabel(const LabelInfo &a,const LabelInfo &b);
	};
	class LabelInfoSet:public vector<LabelInfo>{
	public:
        LabelInfoSet(vector<int> &labels);
        int setOrder();

        void filter(int min_sup);
		
	};

}; 

#endif
