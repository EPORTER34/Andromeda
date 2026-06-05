#pragma once
#include "Satellite/Satellite.hpp"

#include <vector>

class Simulation
{
public:
    Simulation();
    void runTimeStep();
    void setTimeStep(float newTimeStep);
private:
    std::vector<Satellite> satellites;

    float timeStep;
    double time;
};

//things to go in simulation
//array of satellites
//array of ground stations
//sim speed