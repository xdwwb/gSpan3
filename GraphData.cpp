#include "GraphData.h"


Graph &GraphData::buildGraph(Graph &g) {
	for (size_t i = 0;i < vertexLabel.size();i++) {
		if (vertexMask[i] == true) {
			g.addVertex(vertexLabel[i]);
		}
	}
	for (size_t j = 0;j < edgeLabel.size();j++) {
		if (edgeMask[j] == true) {
			g.addEdge(from[j], to[j], edgeLabel[j]);
			g.addEdge(to[j], from[j], edgeLabel[j]);//无向图需要这样做
		}
	}
	return g;
}
