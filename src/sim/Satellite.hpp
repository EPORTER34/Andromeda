#pragma once



class Satellite
{
public:

private:
    float orbitalRadius; //radius of the orbit in km
    float position[3]; //(x,y,z) position of the satellite

    //might remove acceleration later since its only needed to calculate velocity
    //might remove velocity if position can be easily parameterized once in constructor
    float velocity; //tangential velocity of the satellite      =sqrt(g*r)
    float centripAccel; //centripital acceleration              =G*M_e/r^2
    //note: centriptial acceleration is assumed to be constant & tangential
    //      acceleration is assumed to be 0, this only works because the orbits
    //      of non HEO satellites are assumed to be circular
};