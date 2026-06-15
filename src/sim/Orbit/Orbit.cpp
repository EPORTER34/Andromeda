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

std::array<double, 3> Orbit::computePositionECI(double simulationTime) const
{
    double trueAnomaly = fmod(orbitalAngularVelocity * simulationTime + orbitalElements.initialAnomaly, 2*PI);
    double cosV = cos(trueAnomaly), sinV = sin(trueAnomaly);
    double orbitalRadius = orbitalElements.radius;
    
    //standard inclined circular orbit equations for ECI
    double ECIx = orbitalRadius * (cosO * cosV - sinO * sinV * cosI);
    double ECIy = orbitalRadius * (sinO * cosV + cosO * sinV * cosI);
    double ECIz = orbitalRadius * sinV * sinI;

    return {ECIx, ECIy, ECIz};
}

std::array<double, 3> Orbit::computePositionECEF(double simulationTime) const
{
    std::array<double,3> ECI = computePositionECI(simulationTime);

    double earthAngle = fmod(EARTH_ANGULAR_VELOCITY * simulationTime, 2*PI);
    double cosT = cos(earthAngle), sinT = sin(earthAngle);

    return { ECI[0] * cosT + ECI[1] * sinT, 
            -ECI[0] * sinT + ECI[1] * cosT, 
            ECI[2]};
}

std::array<double, 3> Orbit::computeVelocity(double simulationtime) const
{
    std::array<double, 3> pos = computePositionECEF(simulationtime);
    pos = VecOps::normalize(pos);
    std::array<double, 3> unitVel = VecOps::crossProduct(normalVector, pos);
    return VecOps::distributeConstant(unitVel, velocity);
}

std::array<double, 3> Orbit::computeVelocity(std::array<double,3> position) const
{
    std::array<double,3> pos = VecOps::normalize(position);
    std::array<double, 3> unitVel = VecOps::crossProduct(normalVector, pos);
    return VecOps::distributeConstant(unitVel, velocity);
}