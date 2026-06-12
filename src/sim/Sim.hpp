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
    void addSatellite(double newRadius, double newInclination, double newAscendingLongitude, double newAnomaly);
    std::vector<std::array<double,3>> getSatellitePositionsECI();
    std::vector<double> getDopplerShifts(double carrierFrequency, std::array<double,3> baseStationPos);
    
private:
    std::vector<Satellite> satellites;

    float timeStep;
    double time;
};