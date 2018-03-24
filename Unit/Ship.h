#ifndef SHIP_H
#define SHIP_H

#include "Unit.h"
#include "ShipRecord.h"

#include <string>

class Ship : public Unit
{
    public:
        Ship();
        virtual void initialize();
        void loadRecord(ShipRecord r);

        virtual void draw(Shader s);


        void setName(std::string newName);
        void setClass(std::string className);

        std::string getName();
        std::string getClass();
        char getSizeClass();

    private:
        std::string name = "";
        std::string className = "";
        char sizeClass = 'E';


};

#endif // SHIP_H
