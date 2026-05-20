#pragma once
#include "Satellite.hpp"

#include <vector>

class Simulation
{
public:
    Simulation();
    void runTimeStep();
private:
    std::vector<Satellite> satellites;
    
    float timeStep;
    float earthAngle;
};

//things to go in simulation
//array of satellites
//array of ground stations
//sim speed