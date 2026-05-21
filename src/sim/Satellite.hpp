#pragma once
#include <array>

class Satellite
{
public:
    Satellite(double radius, double newInlination, double newAscendingLongitude);
    Satellite(double newRadius, double newInlination, double newAscendingLongitude, double newAnomaly);

    std::array<double, 3> computePosition(double simulationTime) const;
private:

    //keplerian orbital elements
    double initialAnomaly; //position of satellite (angle relative to equatorial plane)
    double orbitalRadius; //radius of the orbit in km
    double ascendingLongitude; //longitude where the ascending part of the orbit passes the equator
    double inclination; //tilt relative to vertical

    double orbitalAngularVelocity;
    //double position[3]; //(x,y,z) position in ECEF coordinates

    //constants used in calculating position
    double cosO;
    double sinO;
    double cosI;
    double sinI;

    //note: orbit is assumed to be circular
};