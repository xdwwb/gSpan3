#ifndef GSPAN_H
#define GSPAN_H

#include"GraphDataSet.h"
#include"GraphSet.h"
#include"Graph.h"
#include<string>
#include<iostream>
#include<fstream>
#include<vector>
#include<time.h>
#include<map>
#include"Edge5.h"
#include"DFScode.h"
#include"Children.h"
#include"EdgeFrequency.h"
#include"FrequentSubGraphSet.h"
using namespace std;

class GSpan{
public:
	
	int min_sup;//最小支持度
	GraphSet &gs;//数据集
	//GraphSet resultSet;//结果集
	FrequentSubGraphSet resultSet;
	
	GSpan(int _min_sup,GraphSet &_gs):min_sup(_min_sup),gs(_gs){ }//设置所需要的参数
	void run();//运行程序
	FrequentSubGraphSet& getResult();
	void show();

private:
    void subGraphMining(FSGraph &gc);//挖掘子图


};

#endif
