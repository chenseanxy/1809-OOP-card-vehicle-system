#include "sch.h"


sch::sch() {
	tArr = 0;
	tDept = 0;
	tDest = 0;
}

sch::sch(timeType tArr, timeType tDept, timeType tDest) {
	this->tArr = tArr;
	this->tDept = tDept;
	this->tDest = tDest;
}


sch::~sch() {
}

ostream & operator<<(ostream &out, const sch &sch) {
	out << sch.tArr << " " << sch.tDept << " " << sch.tDest;
	return out;
}
