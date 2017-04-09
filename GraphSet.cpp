#include "GraphSet.h"

GraphSet::GraphSet() {
	vertex_label_size = 0;
	edge_label_size = 0;
}



GraphSet::GraphSet(GraphDataSet &gds) {
	vertex_label_size = gds.vertex_label_size;
	edge_label_size = gds.edge_label_size;

	for (size_t i = 0;i < gds.size();i++) {
		Graph g;
		g = gds[i].buildGraph(g);
		this->push_back(g);
	}
}



void GraphSet::show() {
	for (size_t i = 0;i < this->size();i++) {
		(*this)[i].show();
	}
}
