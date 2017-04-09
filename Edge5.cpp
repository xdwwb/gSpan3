#include "Edge5.h"

bool Edge5::operator<(const Edge5 &b) const {
	const Edge5 &a = *this;//助记

	if (a.from > a.to) {
		if (b.from < b.to)
			return true;
		else if (a.to < b.to)
			return true;
		else if (a.to == b.to&&a.eLabel < b.eLabel)//为什么不接着比较？
			return true;
	}
	else {
		if (b.from < b.to) {
			if (b.from < a.from)
				return true;
			else if (b.from == a.from) {
				if (a.fromLabel < b.fromLabel)
					return true;
				else if (a.fromLabel == b.fromLabel) {
					if (a.eLabel < b.eLabel)
						return true;
					else if (a.eLabel == b.eLabel) {
						if (a.toLabel < b.toLabel)
							return true;
					}
				}
			}
		}//end if
	}//end else
	return false;
}

bool Edge5::operator>(const Edge5 &b) const {
	const Edge5 &a = *this;
	return b < a;
}

bool Edge5::operator==(const Edge5 &b) const {
	const Edge5 &a = *this;
	if (a.from == b.from&&a.to == b.to&&a.fromLabel == b.fromLabel&&a.eLabel == b.eLabel&&a.toLabel == b.toLabel)
		return true;
	else
		return false;
}

void Edge5::show() {
	cout << from << " " << to << " " << fromLabel << " " << eLabel << " " << toLabel << endl;
}

bool Edge5::forward() {
	return this->from < this->to;
}

bool Edge5::backword() {
	return this->from > this->to;
}
