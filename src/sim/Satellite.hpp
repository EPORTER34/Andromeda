#pragma once

class Satellite
{
public:
    Satellite(float radius, float newInlincation, float newAscendingLongitude);
    Satellite(float newRadius, float newInlincation, float newAscendingLongitude, float newAnomaly);

    const float* getPosition() const;
    void updatePosition(float timeStep, float earthAngle);
private:

    //keplerian orbital elements
    float trueAnomaly; //position of satellite (angle relative to equatorial plane)
    float orbitalRadius; //radius of the orbit in km
    float ascendingLongitude; //longitude where the ascending part of the orbit passes the equator
    float inclination; //tilt relative to vertical

    float orbitalAngularVelocity;
    float position[3]; //(x,y,z) position in ECEF coordinates

    //constants used in calculating position
    float cosO;
    float sinO;
    float cosI;
    float sinI;

    //note: orbit is assumed to be circular
};