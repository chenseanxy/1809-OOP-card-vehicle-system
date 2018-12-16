/*************************
*	sch.h
*	Defines sch (schedule) class
*	Handles vehicle schedule related operations
*************************/

#pragma once
#include "types.h"
#include <ostream>

using namespace std;

class sch {
public:
	timeType tArr;
	timeType tDept;
	timeType tDest;

	sch();
	sch(timeType tArr, timeType tDept, timeType tDest);
	~sch();

	friend ostream& operator<<(ostream&, const sch&);

};

