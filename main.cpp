#include"GraphDataSet.h"
#include"GraphSet.h"
#include"Graph.h"
#include<string>
#include<iostream>
#include<fstream>
#include<vector>
#include<time.h>
#include"Edge5.h"
#include"gSpan.h"
#include"test.h"
#include<stdlib.h>

using namespace std;

int main(int argc,char**argv){

    //保存命令行参数
    ifstream in(argv[1]);
    ofstream out(argv[2]);
    double min_sup_rate=atof(argv[3]);

    //验证输入的命令行参数
    if(argc!=4){
        cerr<<"The number of argument is wrong, please check your input!\n";
        return 0;
    }else if(!in){
        cerr<<"The input file path is invalid, please check your input!\n";
        return 0;

    }else if(!out){
        cerr<<"The output file path is invalid, please check your input!\n";
        return 0;
    }else if(!(min_sup_rate>0&&min_sup_rate<=1)){
        cerr<<"The min_sup_rate argument is invalid, it should between 0 and 1!\n";
        return 0;
    }

    Test test;

    //创建图数据集合对象
    GraphDataSet* gds=new GraphDataSet;
    //读取文件数据
    gds->readFromFile(in);
    //进行根据标号频率重新标号的预处理
    gds->reLabel(min_sup_rate);
    //构建邻接表结构
    GraphSet gs(*gds);
    //gs.show();
    //使用后销毁图数据集合对象，减少内存占用。
    delete gds;
    //图挖掘
    int min_sup=(int)(min_sup_rate*gs.size());
    if(min_sup<1)
        min_sup=1;
    GSpan gSpan(min_sup,gs);
	clock_t begin = clock();
    gSpan.run();
	clock_t end = clock();
    //gSpan.show();
	gSpan.showMaximal();
    //展示结果
    //关闭文件流对象
    in.close();
    out.close();
    clog<<"-----------------------------------------------"<<endl;
    clog<<"gSpan:                        "<<endl;
    clog<<"Graph Set Size:               "<<gSpan.gs.size()<<endl;
    clog<<"Minimum Support Count:        "<<gSpan.min_sup<<endl;
    clog<<"Frequent Subgraph Number:     "<<gSpan.resultSet.size()<<endl;
    clog<<"Use Time:                     "<<end-begin<<"ms"<<endl;
    clog<<"-----------------------------------------------"<<endl;

    return 0;
}
