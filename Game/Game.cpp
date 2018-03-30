#include "Game.h"

Game::Game()
{
    //ctor
}

DBase Game::getDB() {
    return this->db;
}

void Game::initialize() {
    this->db = DBase();
    this->db.loadShipDB("Unit/ShipDB.csv");
}
