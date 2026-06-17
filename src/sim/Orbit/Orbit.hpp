#pragma once
#include <array>

class OrbitalElements
{
public:
    OrbitalElements();
    OrbitalElements(double newRadius, double newInclination, double newRAAN, double newAnomaly);
    
    double initialAnomaly;
    double radius;
    double RAAN;
    double inclination;
    //NOTE: ORBIT ASSUMED CIRCULAR
};

class Orbit
{
public:
    Orbit(OrbitalElements newOrbit);

    std::array<double, 3> computePositionECI(double simulationTime) const;
    std::array<double, 3> computePositionECEF(double simulationTime) const;
    std::array<double, 3> computeVelocity(double simulationtime) const;
    std::array<double, 3> computeVelocity(std::array<double,3> position) const;

private:
    OrbitalElements orbit;
    double orbitalAngularVelocity;

    //constants used in calculating position
    double cosO;
    double sinO;
    double cosI;
    double sinI;

    //constants used in calculating velocity
    std::array<double, 3> normalVector;
    double velocity;
};