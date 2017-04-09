#include "GraphDataSet.h"
#include <algorithm>
#include <vector>


//从文件中读取图数据

void GraphDataSet::readFromFile(ifstream &in) {
	GraphData *gd = NULL;
	char state;
	char temp[30];

	while (in >> state) {
		if (state == 't') {
			if (gd) {
				this->push_back(*gd);//保存原来的图
				delete gd;//销毁
				gd = NULL;//赋值防止访问野指针
			}
			gd = new GraphData;//新建
			in.getline(temp, 30);//跳过这一行

		}
		else if (state == 'v') {
			int vLabel, id;
			in >> id;
			in >> vLabel;
			gd->vertexLabel.push_back(vLabel);//设置顶点标签
			gd->vertexMask.push_back(true);//设置顶点掩码
			//频率统计
			if (vLabels.size() < vLabel + 1)
				vLabels.resize(vLabel + 1, 0);
			vLabels[vLabel]++;

		}
		else if (state == 'e') {
			int from, to, eLabel;
			in >> from;
			in >> to;
			in >> eLabel;
			gd->from.push_back(from);
			gd->to.push_back(to);
			gd->edgeLabel.push_back(eLabel);
			gd->edgeMask.push_back(true);
			//频率统计
			if (eLabels.size() < eLabel + 1)
				eLabels.resize(eLabel + 1, 0);
			eLabels[eLabel]++;
		}
		else {
			cerr << "File format is unsupport!Please check your input!\n";
			exit(0);

		}
	}

	//保存最后一个图的数据
	if (gd) {
		this->push_back(*gd);//保存原来的图
		delete gd;//销毁
		gd = NULL;//赋值防止访问野指针
	}
	//图已经加载完毕了！


}

//对图数据中的标签根据频繁与否进行过滤和重新标号。
void GraphDataSet::reLabel(double min_sup_rate) {
	//设置支持度阈值
	this->min_sup = min_sup_rate*this->size();//double到int没有问题的
	if (min_sup < 1)
		min_sup = 1;
	//建立处理标号频率的类
	LabelInfoSet vertexOrder(vLabels);
	LabelInfoSet edgeOrder(eLabels);
	//对频率进行排序
	sort(vertexOrder.begin(), vertexOrder.end());
	sort(edgeOrder.begin(), edgeOrder.end());
	//获得逆序
	reverse(vertexOrder.begin(), vertexOrder.end());
	reverse(edgeOrder.begin(), edgeOrder.end());
	//过滤非频繁标号
	vertexOrder.filter(min_sup);
	edgeOrder.filter(min_sup);
	//设置序号
	vertex_label_size = vertexOrder.setOrder();
	edge_label_size = edgeOrder.setOrder();
	for (size_t i = 0;i < vertexOrder.size();i++) {
		if (vertexOrder[i].mask == true)
			nodeLabelRecover.push_back(vertexOrder[i].label);
	}

	for (size_t i = 0;i < edgeOrder.size();i++) {
		if (edgeOrder[i].mask == true)
			edgeLabelRecover.push_back(edgeOrder[i].label);
	}

	//根据Label反转排序
	sort(vertexOrder.begin(), vertexOrder.end(), LabelInfo::compareByLabel);
	sort(edgeOrder.begin(), edgeOrder.end(), LabelInfo::compareByLabel);
	//重新标号
	for (size_t i = 0;i < this->size();i++) {//遍历每一个GraphData
		int id = 0;//对顶点赋予新的标号
		//reLabel顶点
		for (size_t j = 0;j < (*this)[i].vertexLabel.size();j++) {//遍历顶点
			int &Label = (*this)[i].vertexLabel[j];//找到此顶点所对应的标签
			if (vertexOrder[Label].mask == false)//此标签非频繁
			{
				(*this)[i].vertexMask[j] = false;//设置不可见
				(*this)[i].newId.push_back(-1);
			}
			else {
				(*this)[i].newId.push_back(id);//赋予新的id
				id++;//id号增长
			}
			Label = vertexOrder[Label].order;//relabel，非频繁的标记为-1
		}
		//reLabel边
		for (size_t k = 0;k < (*this)[i].edgeLabel.size();k++) {//遍历边表
			int &from = (*this)[i].from[k];
			int &to = (*this)[i].to[k];
			bool mask = (*this)[i].edgeMask[k];
			int &Label = (*this)[i].edgeLabel[k];
			vector<int> &v = (*this)[i].vertexLabel;
			vector<int> &ids = (*this)[i].newId;
			vector<bool> &vmask = (*this)[i].vertexMask;

			if (edgeOrder[Label].mask == false)
				(*this)[i].edgeMask[k] = false;//边不频繁

			else if (vmask[from] == false || vmask[to] == false) {
				(*this)[i].edgeMask[k] = false;//边所连接的顶点不频繁
			}
			from = ids[from];//reAssign
			to = ids[to];//reAssign
			Label = edgeOrder[Label].order;//reLabel
		}//end for
	}//end for

}

LabelInfo::LabelInfo(int l, int f, int o) {
	label = l;
	frequency = f;
	order = o;
	mask = true;//默认为真，有待后续处理
}

bool LabelInfo::operator<(LabelInfo &b) {
	return this->frequency < b.frequency ? true : false;
}

bool LabelInfo::compareByLabel(const LabelInfo &a, const LabelInfo &b) {
	return a.label < b.label ? true : false;
}

LabelInfoSet::LabelInfoSet(vector<int> &labels) {
	for (unsigned i = 0;i < labels.size();i++) {
		this->push_back(LabelInfo(i, labels[i], -1));
	}
}

int LabelInfoSet::setOrder() {
	unsigned j = 0;
	for (unsigned i = 0;i < (*this).size();i++) {
		if ((*this)[i].mask) {
			(*this)[i].order = j;
			j++;
		}
	}
	return j;//返回重新标号的数量
}

void LabelInfoSet::filter(int min_sup) {
	for (unsigned i = 0;i < (*this).size();i++) {
		if ((*this)[i].frequency < min_sup)
			(*this)[i].mask = false;
	}
}
