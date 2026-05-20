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
    float cosV = cos(trueAnomaly), sinV = sin(trueAnomaly);
    
    //standard inclined circular orbit equations for ECI
    ECI[0] = orbitalRadius * (cosO * cosV - sinO * sinV * cosI);
    ECI[1] = orbitalRadius * (sinO * cosV + cosO * sinV * cosI);

    //conversion to ECEF
    float cosT = cos(earthAngle), sinT = sin(earthAngle);
    position[0] = ECI[0] * cosT + ECI[1] * sinT;
    position[1] = -ECI[0] * sinT + ECI[1] * cosT; 
    position[2] = orbitalRadius * sinV * sinI;
}