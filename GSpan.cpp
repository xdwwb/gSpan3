#include "GSpan.h"
#include <set>
#include "FSGraph.h"
using namespace std;
//运行程序,算法主要实现在这里
//发现频繁一边，然后直接挖掘子代
void GSpan::run() {
	//如何使用动态数组？
	//int *edgeFrequency=new int[gs.vertex_label_size][gs.edge_label_size][gs.vertex_label_size];
	//EdgeFrequency ef(gs.vertex_label_size,gs.edge_label_size);

	ef.init(gs.vertex_label_size, gs.edge_label_size, min_sup);
	for (size_t i = 0;i < gs.vertex_label_size;i++) {//有序枚举，按照字典序
		for (size_t j = 0;j < gs.edge_label_size;j++) {
			for (size_t k = i;k < gs.vertex_label_size;k++) {//只统计上三角即可！令k从i开始;
				int count = 0;

				for (size_t g = 0;g < gs.size();g++) {
					if (gs[g].hasEdge(i, j, k)) {
						count++;
					}
				}

				ef(i, j, k) = count;
				ef(k, j, i) = count;
			}//end for
		}//end for
	}//end for
	for (size_t i = 0;i < gs.vertex_label_size;i++) {//有序枚举，按照字典序
		for (size_t j = 0;j < gs.edge_label_size;j++) {
			for (size_t k = i;k < gs.vertex_label_size;k++) {//只统计上三角即可！令k从i开始;、

				if (ef(i, j, k) < min_sup)
					continue;
				Edge5 e(0, 1, i, j, k);
				DFScode gc;
				gc.push_back(e);
				FSGraph subGraph;
				subGraph.gc = gc;

				for (size_t g = 0;g < gs.size();g++) {
					if (gs[g].hasEdge(i, j, k)) {
						subGraph.supporter.push_back(g);//加入支持者
					}
				}

				subGraphMining(subGraph);//频繁增长图挖掘

				for (size_t g = 0;g < gs.size();g++) {
					gs[g].removeEdge(i, j, k);
				}
			}//end for
		}//end for
	}//end for
	getMaximal();
}//end run

void GSpan::subGraphMining(FSGraph &subGraph) {
	//cout<<gc[0].fromLabel<<" "<<gc[0].eLabel<<" "<<gc[0].toLabel<<" "<<gc.supporter.size()<<endl;
	//return;
	subGraph.g = subGraph.gc.toGraph(subGraph.g);
	if (!subGraph.gc.isMin(subGraph.g))
		return;

	if (resultSet.size() > 0) {
		if (subGraph.gc.size() > resultSet.back().gc.size())
			resultSet.back().isMaximal = false;
		else
			resultSet.back().isMaximal = true;
	}
	//加入结果集
	resultSet.push_back(subGraph);
	//subGraph = resultSet.back();
	map<Edge5, vector<int>> summary;

	//挖掘子代
	for (size_t i = 0;i < subGraph.supporter.size();i++) {
		//获得一个支持者
		Graph &g = gs[subGraph.supporter[i]];
		Children c(g, subGraph.gc, ef);
		c.getChildren();
		//获得一个子代
		set<Edge5>::iterator itr;
		for (itr = c.begin();itr != c.end();itr++) {
			const Edge5 &child = *itr;
			//最关键的错误终于被我找出来了！
			summary[child].push_back(subGraph.supporter[i]);
		}

	}
	map<Edge5, vector<int>>::iterator itr;

	//subGraph.isMaximal = true;
	//int pre_size = resultSet.size();
	for (itr = summary.begin();itr != summary.end();itr++) {

		//先假设是极大的
		if (itr->second.size() < min_sup)
			continue;
		//如果存在频繁子代，则不是极大的，即使频繁子代的DFScode不是最小的
		//resultSet.back().isMaximal = false;

		//DFScode child_gc = subGraph.gc;//复制父母
		FSGraph childGraph;
		childGraph.gc = subGraph.gc;
		childGraph.gc.push_back(itr->first);//添加增长的边
		//childGraph.gc = child_gc;
		childGraph.supporter = (itr->second);//添加支持者
		subGraphMining(childGraph);//子代挖掘
	}
	//if(pre_size == resultSet.size())//没有子代增长，所以是极大的！
	//	subGraph.isMaximal = false;



}

//获得结果
FrequentSubGraphSet& GSpan::getResult() {
	return resultSet;
}

FrequentSubGraphSet& GSpan::getMaximal() {
	for (size_t i = 0;i < resultSet.size();i++) {
		if (resultSet[i].isMaximal == true)
			maximalResultSet.push_back(resultSet[i]);
	}
	return maximalResultSet;
}
//展示结果
void GSpan::show() {
	cout << "Graph Set Size: " << gs.size() << endl;
	cout << "Minimum Support Count: " << min_sup << endl;
	cout << "Frequent SubGraph Number: " << resultSet.size() << endl;
	cout << endl;

	resultSet.show();
}

void GSpan::showMaximal() {
	cout << "Graph Set Size: " << gs.size() << endl;
	cout << "Minimum Support Count: " << min_sup << endl;
	cout << "Frequent SubGraph Number: " << resultSet.size() << endl;
	cout << "Maximal Frequent SubGraph Number: " << maximalResultSet.size() << endl;
	cout << endl;

	maximalResultSet.show();

}

void GSpan::save(ofstream &nodeList, ofstream &edgeList, FrequentSubGraphSet &gset)
{
	for (size_t i = 0; i < gset.size();i++) {
		nodeList << i << ", " << gset[i].gc[0].fromLabel << endl;
		for (size_t j = 0;j < gset[i].gc.size();j++) {
			Edge5 e = gset[i].gc[j];
			if (e.forward())
				nodeList << i << ", " << e.toLabel << endl;
			edgeList << i << ", " << e.from << ", " << e.to << ", " << e.eLabel << endl;
		}
	}
}

void GSpan::save(ofstream & nodeList, ofstream & edgeList, FrequentSubGraphSet & gset, vector<int> nodeLabelRecover, vector<int> edgeLabelRecover)
{
	for (size_t i = 0; i < gset.size();i++) {
		nodeList << i << ", " << nodeLabelRecover[gset[i].gc[0].fromLabel] << endl;
		for (size_t j = 0;j < gset[i].gc.size();j++) {
			Edge5 e = gset[i].gc[j];
			if (e.forward())
				nodeList << i << ", " << nodeLabelRecover[e.toLabel] << endl;
			edgeList << i << ", " << e.from << ", " << e.to << ", " << edgeLabelRecover[e.eLabel] << endl;
		}
	}
}

