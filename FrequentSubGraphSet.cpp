#include"FrequentSubGraphSet.h"

void FrequentSubGraphSet::show() {
	for (size_t i = 0;i < this->size();i++) {
		cout << "# Graph " << i << endl << endl;
		(*this)[i].show();
		cout << "-----------------------------------------------------------------------------------" << endl;
	}

}