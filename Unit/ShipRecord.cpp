#include "ShipRecord.h"
#include "../Utils/FGDN_Tools.h"

#include <vector>
#include <iostream>

ShipRecord::ShipRecord()
{

}

void ShipRecord::initializeFromStr(std::string &csvLine) {
    //std::cout << "\n\n***NEW RECORD***: " << csvLine << "\n\n";
    std::cout << "LINE: " << csvLine << "\n";

    std::vector<std::string> inp = split(csvLine, ',');

    // Column 1: ID
    setID(std::stoi(inp.at(0)));

    // Column 2: Country
    setCountry(inp.at(1));

    // Column 3: Class Name
    setName(inp.at(2));

    // Column 4: Type Abbreviation
    setType(inp.at(3));

    // Column 5: Displacement
    setDisplacement(std::stoi(inp.at(4)));

    // Column 6: Size Class
    setSizeClass(inp.at(5).at(0));

    // Column 7: DP
    setDP(std::stoi(inp.at(6)));

    // Column 8/9/10/11: Max speed when undamaged, 25%, 50%, and 75%
    setSpdRng(std::stoi(inp.at(7)),
                std::stoi(inp.at(8)),
                std::stoi(inp.at(9)),
                std::stoi(inp.at(10)));
}

void ShipRecord::setID(int idNum)           {this->id = idNum; }
void ShipRecord::setName(std::string name)  {this->className = name; }
void ShipRecord::setCountry (std::string cName) {this->countryName = cName; }
void ShipRecord::setType(std::string sType) {this->shipType = sType; }
void ShipRecord::setDisplacement(int disp)  {this->displacement = disp; }
void ShipRecord::setSizeClass(char sClass)  {this->sizeClass = sClass; }
void ShipRecord::setDP(int dPoints)         {this->dp = dPoints; }
void ShipRecord::setSpdRng(int none, int qtr, int half, int threeQtrs) {
    this->spdRange.clear();
    this->spdRange.push_back(none);
    this->spdRange.push_back(qtr);
    this->spdRange.push_back(half);
    this->spdRange.push_back(threeQtrs);
}

int ShipRecord::getShipClassID()            { return this->id;}
std::string ShipRecord::getShipClassName()  { return this->className; }
std::string ShipRecord::getShipClassCountry() { return this->countryName; }
std::string ShipRecord::getShipClassType()  { return this->shipType; }
int ShipRecord::getShipClassDisplacement()  { return this->displacement; }
char ShipRecord::getShipClassSize()         { return this->sizeClass; }
int ShipRecord::getShipClassDP()            { return this->dp; }
std::vector<int> ShipRecord::getShipClassSpdRng() { return this->spdRange; }


int ShipRecord::getID() {return this->id; }
std::string ShipRecord::printSummary() {
    return ("ID: " + std::to_string(this->id) + ", Class name: " + this->className +
                " from country " + this->countryName);
}
