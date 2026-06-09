#pragma once
#include "Satellite/Satellite.hpp"

#include <vector>
#include <array>

class Simulation
{
public:
    Simulation();
    void runTimeStep();
    void setTimeStep(float newTimeStep);
    std::vector<std::array<double,3>> getSatellitePositions();
    std::vector<double> getDopplerShifts(double carrierFrequency, std::array<double,3> baseStationPos);
private:
    std::vector<Satellite> satellites;

    float timeStep;
    double time;
};

//things to go in simulation
//array of satellites
//array of ground stations
//sim speed