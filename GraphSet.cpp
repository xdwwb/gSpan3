#include "GraphSet.h"

GraphSet::GraphSet() {
	vertex_label_size = 0;
	edge_label_size = 0;
}



GraphSet::GraphSet(int vertexLabelSize, int edgeLabelSize) {
	vertex_label_size = vertexLabelSize;
	edge_label_size = edgeLabelSize;
}



void GraphSet::show() {
	for (size_t i = 0;i < this->size();i++) {
		(*this)[i].show();
	}
}
