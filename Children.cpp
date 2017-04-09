#include"Children.h"

void Children::getChildren() {

	graph2code.resize(0);
	graph2code.resize(g.vertexLabel.size(), -1);

	code2graph.resize(0);
	code2graph.resize(g.vertexLabel.size(), -1);

	edgeVisited.resize(0);
	for (size_t i = 0;i < g.vertexLabel.size();i++) {
		vector<bool> temp;
		temp.resize(0);
		temp.resize(g.vertexLabel.size(), false);
		edgeVisited.push_back(temp);
	}
	//寻找最右路径
	rmPath.resize(0);
	rmPath.resize(gc.size() + 1, -1);
	for (size_t i = 0;i < gc.size();i++) {
		if (gc[i].forward() && gc[i].to > rmPath[gc[i].from]) {
			rmPath[gc[i].from] = gc[i].to;
		}
	}

	//匹配第一个顶点和接下来的匹配过程
	for (size_t i = 0;i < g.vertexLabel.size();i++) {
		if (gc[0].fromLabel != g.vertexLabel[i])
			continue;
		graph2code[i] = 0;
		code2graph[0] = (int)i;
		DFS(0);
		graph2code[i] = -1;
		code2graph[0] = -1;
	}
}

void Children::DFS(int current) {

	//匹配完成，生成子代
	if (current >= gc.size()) {
		//从最右路径扩展，注意次序！
		vector<int> rmPoint;
		rmPoint.push_back(0);
		//整理最右路径上的节点
		for (size_t i = 0;rmPath[i] > -1;i = rmPath[i]) {
			rmPoint.push_back(rmPath[i]);
		}
		//这里的变量i不能为unsigned类型，真有意思，仔细分析一下就知道了！
		for (size_t i = 0;i < rmPoint.size();i++) {
			int from = code2graph[rmPoint[i]];
			int fromLabel = g.vertexLabel[from];
			for (size_t j = 0;j < g.edgeLabel[from].size();j++) {
				int to = g.edgeTo[from][j];
				int eLabel = g.edgeLabel[from][j];
				int toLabel = g.vertexLabel[to];

				if (edgeVisited[from][to])
					continue;
				//最右顶点的处理情况

				//剪枝策略:剪除非频繁的增长
				if (ef(fromLabel, eLabel, toLabel) < ef.min_sup)
					continue;

				//剪枝策略:剪除比第一条边小的边的增长
				Edge5 e(0, 1, fromLabel, eLabel, toLabel);
				if (e < gc[0])
					continue;
				assert(gc[0] < e || gc[0] == e);//我猜这条剪枝策略是不必要的！

				if (i == rmPoint.size() - 1) {
					if (graph2code[to] > -1) {//发现旧的节点
						Edge5 e(graph2code[from], graph2code[to], fromLabel, eLabel, toLabel);
						assert(e.backword());
						//if(e.forward())//理应为后向的边
						//  continue;
						this->insert(e);
					}
					else {//发现新的节点
						Edge5 e(graph2code[from], rmPoint.back() + 1, fromLabel, eLabel, toLabel);
						this->insert(e);
					}
				}
				else {
					//非最右顶点的处理情况
					if (graph2code[to] > -1)
						continue;
					Edge5 e(graph2code[from], rmPoint.back() + 1, fromLabel, eLabel, toLabel);
					this->insert(e);
				}

			}

		}

		return;
	}
	//继续匹配
	Edge5& e = gc[current];
	int from = code2graph[e.from];
	int fromLabel = g.vertexLabel[from];

	//起始标签一定匹配过了
	assert(fromLabel == e.fromLabel);

	for (size_t i = 0;i < g.edgeTo[from].size();i++) {

		int to = g.edgeTo[from][i];
		int toLabel = g.vertexLabel[to];
		int eLabel = g.edgeLabel[from][i];

		//此边已经访问过了
		if (edgeVisited[from][to] == true)
			continue;

		//边不匹配
		if (e.eLabel != eLabel)
			continue;
		//终止节点不匹配
		if (e.toLabel != toLabel)
			continue;
		//边的标号匹配成功

		if (e.forward() && graph2code[to] == -1) {
			edgeVisited[from][to] = true;
			edgeVisited[to][from] = true;
			graph2code[to] = e.to;
			code2graph[e.to] = to;
			DFS(current + 1);
			graph2code[to] = -1;
			code2graph[e.to] = -1;
			edgeVisited[from][to] = false;
			edgeVisited[to][from] = false;
		}
		else if (e.backword() && graph2code[to] > -1) {
			//这里不太对！
			edgeVisited[from][to] = true;
			edgeVisited[to][from] = true;
			DFS(current + 1);
			edgeVisited[from][to] = false;
			edgeVisited[to][from] = false;
		}
		//另外还有两种非法的情况！
	}
}
