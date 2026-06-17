#include "Orbit.hpp"
#include "../../util/constants.hpp"
#include "../../util/VectorOperations/VectorOperations.hpp"

#include <cmath>

OrbitalElements::OrbitalElements()
{
    radius = inclination = RAAN = initialAnomaly = 0;
}

OrbitalElements::OrbitalElements(double newRadius, double newInclination, double newRAAN, double newAnomaly)
{
    radius = newRadius;
    inclination = newInclination;
    RAAN = newRAAN;
    initialAnomaly = newAnomaly;
}

//angles are in radians
Orbit::Orbit(OrbitalElements newOrbit) : orbit(newOrbit)
{
    orbitalAngularVelocity = sqrt(MU_EARTH / pow(orbit.radius,3));
    cosO = cos(orbit.RAAN);
    sinO = sin(orbit.RAAN);
    cosI = cos(orbit.inclination);
    sinI = sin(orbit.inclination);
    normalVector = {sinI * sinO, -sinI * sinO, cosI};
    velocity = orbitalAngularVelocity * orbit.radius;
}

std::array<double, 3> Orbit::computePositionECI(double simulationTime) const
{
    double trueAnomaly = fmod(orbitalAngularVelocity * simulationTime + orbit.initialAnomaly, 2*PI);
    double cosV = cos(trueAnomaly), sinV = sin(trueAnomaly);
    
    //standard inclined circular orbit equations for ECI
    double ECIx = orbit.radius * (cosO * cosV - sinO * sinV * cosI);
    double ECIy = orbit.radius * (sinO * cosV + cosO * sinV * cosI);
    double ECIz = orbit.radius * sinV * sinI;

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