#pragma once
#include <array>

class OrbitalElements
{
public:
    OrbitalElements(double newRadius, double newInlination, double newAscendingLongitude, double newAnomaly);
    double initialAnomaly;
    double radius;
    double ascendingLongitude;
    double inclination;
    //NOTE: ORBIT ASSUMED CIRCULAR
};

class Satellite
{
public:
    Satellite(double newRadius, double newInclination, double newAscendingLongitude, double newAnomaly);

    std::array<double, 3> computePosition(double simulationTime) const;

private:
    OrbitalElements orbitalElements;
    double orbitalAngularVelocity;

    //constants used in calculating position
    double cosO;
    double sinO;
    double cosI;
    double sinI;
};