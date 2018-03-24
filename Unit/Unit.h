#ifndef UNIT_H
#define UNIT_H

#include <glm/glm.hpp>
#include "../Shader.h"


class Unit
{
    public:
        Unit();
        virtual void initialize() = 0;

        virtual void draw(Shader s) = 0;


        void moveTime(double deltaSeconds);

        void setHeading(double newHeading);
        void changeHeadingBy(double delta);

        void setPos(glm::dvec3 newPos);
        void changePosBy(glm::dvec3 delta);

        // Setting velocity affects heading, speed, and pitch
        void setVelocity(glm::dvec3 newVelo);
        void changeVelocityBy(glm::dvec3 delta);

        // Setting speed affects velocity
        void setSpeed(double newSpeed);
        void changeSpeedBy(double delta);

        double getHeading();
        double getPitch();
        double getSpeed();
        double getTgtSpeed();
        glm::dvec3 getVelo();
        glm::dvec3 getPos();


    protected:

        double heading = 0.0;                            // Degrees
        double pitch = 0.0;                              // Degrees
        glm::dvec3 pos = glm::dvec3(0.0, 0.0, 0.0);      // Meters

        glm::dvec3 velocity = glm::dvec3(0.0, 0.0, 0.0); // m/s
        double speed = 0.0;                              // m/s
        double tgtSpeed = 0.0;                           // m/s

    private:
};

#endif // UNIT_H
