#include "Satellite.hpp"
#include "../../util/constants.hpp"

#include <cmath>

//angles are in radians
//prograde orbits: 0 < I < PI/2
//polar orbit: I = PI/2
//retrograde orbits: PI/2 < I < PI
Satellite::Satellite(double newRadius, double newInlination, double newAscendingLongitude)
{
    initializeSatellite(newRadius, newInlination, newAscendingLongitude);
    initialAnomaly = 0;
}
Satellite::Satellite(double newRadius, double newInlination, double newAscendingLongitude, double newAnomaly)
{
    initializeSatellite(newRadius, newInlination, newAscendingLongitude);
    initialAnomaly = newAnomaly;
}

void Satellite::initializeSatellite(double newRadius, double newInlination, double newAscendingLongitude)
{  
    orbitalRadius = newRadius;
    inclination = newInlination;
    ascendingLongitude = newAscendingLongitude;
    
    orbitalAngularVelocity = sqrt(MU_EARTH / pow(newRadius,3));
    cosO = cos(ascendingLongitude);
    sinO = sin(ascendingLongitude);
    cosI = cos(inclination);
    sinI = sin(inclination);
}

//computes position in ECEF & returns in array
std::array<double, 3> Satellite::computePosition(double simulationTime) const
{
    double trueAnomaly = orbitalAngularVelocity * simulationTime + initialAnomaly;
    double cosV = cos(trueAnomaly), sinV = sin(trueAnomaly);

    //standard inclined circular orbit equations for ECI
    double ECIx = orbitalRadius * (cosO * cosV - sinO * sinV * cosI);
    double ECIy = orbitalRadius * (sinO * cosV + cosO * sinV * cosI);

    //conversion to ECEF
    double earthAngle = EARTH_ANGULAR_VELOCITY * simulationTime;
    double cosT = cos(earthAngle), sinT = sin(earthAngle);

    return { ECIx * cosT + ECIy * sinT, 
            -ECIx * sinT + ECIy * cosT, 
            orbitalRadius * sinV * sinI};
}