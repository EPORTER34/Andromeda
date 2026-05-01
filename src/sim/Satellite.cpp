#include "Satellite.hpp"
#include "../util/constants.hpp"

#include <cmath>

Satellite::Satellite(float newRadius, float newInlincation, float newAscendingLongitude)
{
    netAngularVelocity = sqrt(G * MASS_EARTH / newRadius) * newRadius - EARTH_ANGULAR_VELOCITY;

    orbitalRadius = newRadius;
    inclination = newInlincation;
    ascendingLongitude = newAscendingLongitude;
    trueAnomoly = 0; //might add seperate constructor to set initial anomoly
}