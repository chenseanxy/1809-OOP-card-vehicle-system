#pragma once

#include "types.h"
#include "cardDB.h"
#include "vehDB.h"
#include "message.h"
#include "main.h"

namespace ui {
	Status ui();
	Status cardReader();
	Status cardDBOps();
	Status vehOps();
	Status vehDBOps();
}