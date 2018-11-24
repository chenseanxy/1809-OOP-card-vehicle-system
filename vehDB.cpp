#include "vehDB.h"
#include "msg.h"
#include <fstream>
#include <ostream>

vehDB::vehDB() {
	msg::backendInfo("Constructing vehDB");
	readFromDisk();
}

vehDB::~vehDB() {
	msg::backendInfo("Destroying vehDB");
	writeToDisk();
}

Status vehDB::add(vIDType vehNum, veh v) {
	if (vehMap.find(vehNum) != vehMap.end()) {
		msg::backendErr("Cannot add vehicle " + to_string(vehNum) + v.getLicense() + " , veh exists");
		return -1;
	}

	pair<vehMapType::iterator, bool> addResult;
	addResult = vehMap.insert(pair<vIDType, veh>(vehNum, v));
	if (addResult.second) {
		msg::backendInfo("Added veh " + to_string(vehNum));
		return 0;
	}

	msg::backendErr("Cannot add vehicle " + to_string(vehNum) + ", undefined error");
	return 1;
}

veh & vehDB::find(vIDType vehNum) {
	vehMapType::iterator iter = vehMap.find(vehNum);
	if (iter == vehMap.end()) {
		msg::backendErr("Vehicle not found: " + to_string(vehNum));
		return vehDB::emptyVeh;
	}

	return iter->second;
}

void vehDB::display() {
	msg::debug("----Start printing vehicle DB----");
	vehMapType::iterator iter;
	for (iter = vehMap.begin(); iter != vehMap.end(); iter++) {
		msg::debug("Vehicle Number: " + to_string(iter->first));
		iter->second.print();
		msg::debug("");
	}
	msg::debug("-----End printing vehicle DB----");
}

Status vehDB::writeToDisk() {
	msg::backendInfo("Writing vehDB to disk");
	fstream dbFile("vehDB.txt");
	if (!dbFile.is_open()) {
		msg::backendErr("Cannot write to vehDB.txt");
		return -1;
	}

	vehMapType::iterator it;
	for (it = vehMap.begin(); it != vehMap.end(); it++) {
		dbFile << it->first << " "
			<< it->second.getLicense() << " "
			<< it->second.getDriver() << " "
			<< it->second.getMaxLoad() << " "
			<< it->second.getSch() << " "
			<< it->second.getNextVeh() << " "
			<< std::endl;
	}
	dbFile.close();
	return 0;
}

Status vehDB::readFromDisk() {
	ifstream dbFile("vehDB.txt");
	if (!dbFile.is_open()) {
		msg::backendErr("Can't open dbFile");
		return 1;
	}

	vehMap.clear();
	char buffer[MAX_DB_LINE_LEN];
	char licenseBuffer[BUF_LEN] = { 0 }, driverBuffer[BUF_LEN] = { 0 };
	vIDType vehNum, nextVeh;
	vLoadType load, maxLoad;
	timeType tArr, tDept, tDest;
	int scanCount;
	
	while (!dbFile.eof()) {
		dbFile.getline(buffer, MAX_DB_LINE_LEN);

		if (buffer[0] == 0 || buffer[0] == '#') {
			continue;
		}

		scanCount = sscanf(buffer, "%hu %s %s %hu %lld %lld %lld %hu", &vehNum, licenseBuffer, driverBuffer, &maxLoad, &tArr, &tDept, &tDest, &nextVeh);
		if (scanCount != 8) {
			msg::dbFileReadError(string(buffer));
			vehMap.clear();
			return -1;
		}

		string license(licenseBuffer), driver(driverBuffer);
		sch s(tArr, tDept, tDest);
		veh v(license, driver, maxLoad, s, nextVeh);
		add(vehNum, v);

	}
	return 0;

}
