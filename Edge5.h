#ifndef EDGE5_H
#define EDGE5_H
#include <iostream>

using namespace std;
class Edge5 {
public:
	int from;
	int to;
	int fromLabel;
	int toLabel;
	int eLabel;

	Edge5(int f, int t, int fl, int el, int tl) :from(f), to(t), fromLabel(fl), eLabel(el), toLabel(tl) {}
	bool operator<(const Edge5 &b)const;

	bool operator>(const Edge5 &b)const;
	bool operator==(const Edge5 &b)const;

	void show();
	bool forward();
	bool backword();
};

#endif
