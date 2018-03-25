#include "DB_Loader.h"

#include <fstream>
#include <iostream>

std::map <int, ShipRecord> loadShipDB(std::string dbFile) {


    std::map <int, ShipRecord> shipDB;
    std::ifstream inFile(dbFile);

    if (!inFile) {
        std::cout << "ERROR reading database file: " << dbFile << "\n";
        return shipDB;
    }

    std::string strInput = "";
    getline(inFile, strInput, (char)13);    // Remove header row

    while (!inFile.eof()) {
        ShipRecord newShip = ShipRecord();
        getline(inFile, strInput, (char)13);
        newShip.initializeFromStr(strInput);
        shipDB[newShip.getID()] = newShip;
    }

    std::cout << "Ship DB loaded from " << dbFile <<
        ": " << shipDB.size() << " records loaded.\n";

    return shipDB;
}
