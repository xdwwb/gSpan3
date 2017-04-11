#ifndef GSPAN_H
#define GSPAN_H

#include <map>
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <time.h>
#include "Graph.h"
#include "Edge5.h"
#include "DFScode.h"
#include "Children.h"
#include "GraphSet.h"
#include "GraphDataSet.h"
#include "EdgeFrequency.h"
#include "FrequentSubGraphSet.h"
using namespace std;

class GSpan {
public:

	int min_sup;//最小支持度

	GraphSet &gs;//数据集

	FrequentSubGraphSet resultSet;//频繁子图结果集

	FrequentSubGraphSet maximalResultSet;//极大频繁子图结果集

	GSpan(int _min_sup, GraphSet &_gs) :min_sup(_min_sup), gs(_gs) { }//设置所需要的参数

	void run();//运行程序

	FrequentSubGraphSet& getResult();//获取频繁子图

	FrequentSubGraphSet& getMaximal();//获取极大频繁子图

	void show();//向控制台输出频繁子图挖掘信息

	void showMaximal();//向控制台输出极大频繁子图挖掘信息

	void save(ofstream &nodeList, ofstream &edgeList, FrequentSubGraphSet &gset);

	void save(ofstream &nodeList, ofstream &edgeList, FrequentSubGraphSet &gset, vector<int>nodeLabelRecover, vector<int>edgeLabelRecover);


private:
	void subGraphMining(FSGraph &gc);//挖掘子图

	EdgeFrequency ef;


};

#endif
