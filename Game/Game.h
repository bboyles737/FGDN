#ifndef GAME_H
#define GAME_H

#include "DBase.h"

class Game
{
    public:
        Game();

        void initialize();
        DBase getDB();

    protected:

    private:
        DBase db;


};

#endif // GAME_H
