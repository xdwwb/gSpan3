#ifndef EDGEFREQUENCY_H
#define EDGEFREQUENCY_H



class EdgeFrequency{
public:
	int *dynamicArray;
	int x,y,z;
	int min_sup;
public:
    void init(int node_label_size,int edge_label_size,int _min_sup);
    int& operator()(int fromLabel,int eLabel,int toLabel);

	~EdgeFrequency(){
		delete[] dynamicArray;
	}

};



extern EdgeFrequency ef;

#endif
