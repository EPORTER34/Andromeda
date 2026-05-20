#include "Satellite.hpp"
#include "../util/constants.hpp"

#include <cmath>

//angles are in radians
//prograde orbits: 0 < I < PI/2
//polar orbit: I = PI/2
//retrograde orbits: PI/2 < I < PI
Satellite::Satellite(float newRadius, float newInlincation, float newAscendingLongitude)
{
    orbitalAngularVelocity = sqrt(G * MASS_EARTH / pow(newRadius,3));
    orbitalRadius = newRadius;
    inclination = newInlincation;
    ascendingLongitude = newAscendingLongitude;
    trueAnomaly = 0;

    cosO = cos(ascendingLongitude);
    sinO = sin(ascendingLongitude);
    cosI = cos(inclination);
    sinI = sin(inclination);
}
Satellite::Satellite(float newRadius, float newInlincation, float newAscendingLongitude, float newAnomaly)
{
    orbitalAngularVelocity = sqrt(G * MASS_EARTH / pow(newRadius,3));
    orbitalRadius = newRadius;
    inclination = newInlincation;
    ascendingLongitude = newAscendingLongitude;
    trueAnomaly = 0;

    cosO = cos(ascendingLongitude);
    sinO = sin(ascendingLongitude);
    cosI = cos(inclination);
    sinI = sin(inclination);
}

const float* Satellite::getPosition() const { return position; }

//earthAngle is the current rotational angle of the earth
//updates the position of the satellite in ECEF coordinates & stores in position array
void Satellite::updatePosition(float timeStep, float earthAngle)
{
    trueAnomaly += orbitalAngularVelocity * timeStep;

    float ECI[2]; //temporary array for ECI coodinates (no z)
    //standard inclined circular orbit equations for ECI
    ECI[0] = orbitalRadius * (cosO * cos(trueAnomaly) - sinO * sin(trueAnomaly) * cosI);
    ECI[1] = orbitalRadius * (sinO * cos(trueAnomaly) + cosO * sin(trueAnomaly) * cosI);

    //conversion to ECEF
    position[0] = ECI[0] * cos(earthAngle) + ECI[1] * sin(earthAngle);
    position[1] = -ECI[0] * sin(earthAngle) + ECI[1] * cos(earthAngle); 
    position[2] = orbitalRadius * sin(trueAnomaly) * sinI;
}