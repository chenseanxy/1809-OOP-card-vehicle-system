#pragma once
#include "types.h"
#include "sch.h"
#include <map>

using namespace std;

typedef map<schNumType, sch> schMapType;

class schDB {
	schMapType schMap;

public:
	schDB();
	~schDB();

	Status add(schNumType schNum, sch s);
	sch& find(schNumType sch);

	void display();

	Status writeToDisk();
	Status readFromDisk();
};

