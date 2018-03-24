#ifndef SHIPRECORD_H
#define SHIPRECORD_H

#include <string>
#include <vector>

class ShipRecord
{
    public:
        ShipRecord();

        void setID(int id);
        void setName(std::string className);
        void setType(std::string shipType);
        void setDisplacement(int displacement);
        void setSizeClass(char sizeClass);
        void setDP(int dp);
        void setSpdRng(int noDmg, int qtrDmg, int hlfDmg, int threeQtrsDmg);

    private:
        int id = 0;

        std::string className = "";
        std::string shipType = "";      // Abbreviation, e.g. BB
        int displacement = 0;
        char sizeClass = 'E';

        int dp = 0;                 // Damage point capacity
        std::vector<int> spdRange;  // Speed at 0%, 25%, 50%, 75% damage

        // TODO: Weaponry
};

#endif // SHIPRECORD_H
