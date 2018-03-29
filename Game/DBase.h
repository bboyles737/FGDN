#ifndef DBASE_H
#define DBASE_H

#include <map>
#include <string>

#include "../Unit/ShipRecord.h"
#include "../Unit/Ship.h"

class DBase
{
    public:
        DBase();
        void loadShipDB(std::string dbFile);

        ShipRecord getShipRec(int classID);
        Ship spawnShip(int classID);

    private:
        std::map <int, ShipRecord> shipDB;
};

#endif // DBASE_H
