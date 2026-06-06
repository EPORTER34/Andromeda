#include "Orbit.hpp"
#include "../../util/constants.hpp"
#include "../../util/VectorOperations/VectorOperations.hpp"

#include <cmath>

OrbitalElements::OrbitalElements(double newRadius, double newInlination, double newAscendingLongitude, double newAnomaly)
{
    radius = newRadius;
    inclination = newInlination;
    ascendingLongitude = newAscendingLongitude;
    initialAnomaly = newAnomaly;
}

//angles are in radians
Orbit::Orbit(double newRadius, double newInclination, double newAscendingLongitude, double newAnomaly) 
: orbitalElements(newRadius,newInclination,newAscendingLongitude,newAnomaly)
{
    orbitalAngularVelocity = sqrt(MU_EARTH / pow(newRadius,3));
    cosO = cos(newAscendingLongitude);
    sinO = sin(newAscendingLongitude);
    cosI = cos(newInclination);
    sinI = sin(newInclination);
    normalVector = {sinI * sinO, -sinI * sinO, cosI};
    velocity = orbitalAngularVelocity * newRadius;
}

std::array<double, 3> Orbit::computePosition(double simulationTime) const
{
    double trueAnomaly = orbitalAngularVelocity * simulationTime + orbitalElements.initialAnomaly;
    double cosV = cos(trueAnomaly), sinV = sin(trueAnomaly);
    double orbitalRadius = orbitalElements.radius;

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

std::array<double, 3> Orbit::computeVelocity(double simulationtime) const
{
    std::array<double, 3> pos = computePosition(simulationtime);
    pos = VecOps::normalize(pos);
    std::array<double, 3> unitVel = VecOps::crossProduct(normalVector, pos);
    return VecOps::distributeConstant(unitVel, velocity);
}