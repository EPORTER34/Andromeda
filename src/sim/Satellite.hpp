#pragma once
#include <initializer_list>


class Satellite
{
public:
    Satellite(std::initializer_list<float> initialPosition, float orbitalRadius);
private:
    
    float position[3]; //(x,y,z) position of the satellite

    //might remove acceleration later since its only needed to calculate velocity
    //might remove velocity if position can be easily parameterized once in constructor
    float velocity[3]; //tangential velocity of the satellite      magnitude=sqrt(g*r)
    float centripAccel; //centripital acceleration              =G*M_e/r^2
    //note: centriptial acceleration is assumed to be constant & tangential
    //      acceleration is assumed to be 0, this only works because the orbits
    //      of non HEO satellites are assumed to be circular


    //keplerian orbital elements
    float trueAnomoly; //position of satellite (angle relative to equatorial plane)
    float orbitalRadius; //radius of the orbit in km
    float ascendingLongitude; //longitude where the ascending part of the orbit passes the equator
    float inclination; //title relative to vertical
};