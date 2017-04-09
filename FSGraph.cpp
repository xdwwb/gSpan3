#include "FSGraph.h"


void FSGraph::show() {
	cout << "Support Count: " << supporter.size() << endl;
	cout << "Maximal: " << isMaximal << endl;
	cout << "Supporter: ";
	for (size_t i = 0;i < supporter.size();i++) {
		cout << supporter[i] << " ";
	}
	cout << endl << endl;
	cout << "Graph: " << endl;
	g.show();
	gc.show();
}