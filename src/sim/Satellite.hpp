#pragma once

class Satellite
{
public:
    Satellite(float radius, float newInlincation, float newAscendingLongitude);
private:
    float netAngularVelocity;

    //keplerian orbital elements
    float trueAnomoly; //position of satellite (angle relative to equatorial plane)
    float orbitalRadius; //radius of the orbit in km
    float ascendingLongitude; //longitude where the ascending part of the orbit passes the equator
    float inclination; //tilt relative to vertical

    //note: orbit is assumed to be circular
};