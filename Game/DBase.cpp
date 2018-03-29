#include "DBase.h"

#include <fstream>
#include <iostream>
#include <stdexcept>

DBase::DBase() {

}

ShipRecord DBase::getShipRec(int classID) {
    if (this->shipDB.count(classID) == 0) {
        std::cerr << "ERROR: Attempted to retrieve ship class " << classID << " but class not in database.\n";
        throw std::invalid_argument("");
    }
    return this->shipDB[classID];
}

Ship DBase::spawnShip(int classID) {
    return Ship();
}

void DBase::loadShipDB(std::string dbFile) {
    std::ifstream inFile(dbFile);

    if (!inFile) {
        std::cerr << "ERROR reading database file: " << dbFile << "\n";
        return;
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

    return;
}
