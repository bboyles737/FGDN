#ifndef DB_LOADER_H
#define DB_LOADER_H

#include "ShipRecord.h"

#include <map>
#include <string>



std::map <int, ShipRecord> loadShipDB(std::string dbFile);


#endif // DB_LOADER_H
