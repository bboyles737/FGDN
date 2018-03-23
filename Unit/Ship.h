#ifndef SHIP_H
#define SHIP_H

#include "Unit.h"

#include <string>

class Ship : public Unit
{
    public:
        Ship();
        virtual void initialize();

        virtual void draw(Shader s);


        void setName(std::string newName);
        void setClass(std::string className);

        std::string getName();
        std::string getClass();

    private:
        std::string name = "";
        std::string className = "";


};

#endif // SHIP_H
