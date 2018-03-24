#include "ShipRecord.h"

ShipRecord::ShipRecord()
{

}

void ShipRecord::setID(int idNum)           {this->id = idNum; }
void ShipRecord::setName(std::string name)  {this->className = name; }
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
