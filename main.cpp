#include "main.h"

cardDB cdb;
vehDB vdb;

int main() {

	cdb.readFromDisk();
	vdb.readFromDisk();
	
	
	ui::ui();


	cdb.writeToDisk();
	vdb.writeToDisk();

	return 0;
}


