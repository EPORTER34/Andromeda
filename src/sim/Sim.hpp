#pragma once
#include "Satellite/Satellite.hpp"

#include <vector>
#include <array>
#include <string>

class Simulation
{
public:
    Simulation();
    void runTimeStep();
    float getTimeStep() const;
    void setTimeStep(float newTimeStep);
    double getSimTime() const;
    void setSimTime(double newSimTime);
    void addSatellite(std::string newName, OrbitalElements newOrbit);
    std::vector<std::array<double,3>> getSatellitePositionsECI();
    std::vector<double> getDopplerShifts(double carrierFrequency, std::array<double,3> baseStationPos);
    std::vector<Losses> calculateLosses(double carrierFrequency, std::array<double,3> baseStationPos);
    
private:
    std::vector<Satellite> satellites;

    float timeStep;
    double time;
};