#include "Ship.h"
#include "../Shader.h"


#include <iostream>

Ship::Ship()
{

}

void Ship::initialize() {

}

void Ship::draw(Shader s) {
    std::cout << "Draw!\n";
}

void Ship::setName(std::string newName) {
    this->name = newName;
}

void Ship::setClass(std::string newName) {
    this->className = newName;
}

std::string Ship::getName() { return this->name; }
std::string Ship::getClass() { return this->className; }
