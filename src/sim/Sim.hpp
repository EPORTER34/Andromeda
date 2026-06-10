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
    double getSimTime() const;
    void setSimTime(double newSimTime);
    std::vector<std::array<double,3>> getSatellitePositions();
    std::vector<double> getDopplerShifts(double carrierFrequency, std::array<double,3> baseStationPos);
    
private:
    std::vector<Satellite> satellites;

    float timeStep;
    double time;
};