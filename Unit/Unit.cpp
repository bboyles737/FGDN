#include "Unit.h"

#include "../Utils/FGDN_Tools.h"

#include <cmath>
#include <iostream>

Unit::Unit()
{

}

void Unit::moveTime(double deltaSeconds) {
    this->pos += this->velocity * deltaSeconds;
}

void Unit::setHeading(double newHeading) {
    this->heading = normDegrees(newHeading);
}

void Unit::changeHeadingBy(double delta) {
    setHeading(this->heading + delta);
}

void Unit::setPos(glm::dvec3 newPos) {
    this->pos = newPos;
}

void Unit::changePosBy(glm::dvec3 delta) {
    this->pos += delta;
}

void Unit::setVelocity(glm::dvec3 newVelo) {
    this->velocity = newVelo;
    this->speed = glm::length(newVelo);

    // Flip x and y axis in atan2 so +x axis is 90 degrees (East)
    this->heading = rad_to_deg(atan2(newVelo.x, newVelo.y));
    this->pitch = rad_to_deg(asin(newVelo.z));
}

void Unit::changeVelocityBy(glm::dvec3 delta) {
    setVelocity(this->velocity + delta);
}

void Unit::setSpeed(double newSpeed) {
    double headingRad = deg_to_rad(this->heading);
    double pitchRad = deg_to_rad(this->pitch);
    glm::dvec3 velo = glm::dvec3(sin(headingRad), cos(headingRad), sin(pitchRad)) * newSpeed;
    setVelocity(velo);
}

double Unit::getHeading() { return this->heading; }
glm::dvec3 Unit::getPos() { return this->pos; }
