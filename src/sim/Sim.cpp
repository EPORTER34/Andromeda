#include "Sim.hpp"
#include "../util/constants.hpp"

Simulation::Simulation()
{
    time = 0;
    timeStep = 100;
}

void Simulation::runTimeStep()
{
    time += timeStep;
}

float Simulation::getTimeStep() const
{
    return timeStep;
}

void Simulation::setTimeStep(float newTimeStep)
{
    timeStep = newTimeStep;
}

double Simulation::getSimTime() const
{
    return time;
}

void Simulation::setSimTime(double newSimTime)
{
    time = newSimTime;
}

void Simulation::addSatellite(std::string newName, OrbitalElements newOrbit)
{
    Satellite newSatellite(newName, newOrbit);
    satellites.push_back(newSatellite);
}

std::vector<std::array<double,3>> Simulation::getSatellitePositionsECI()
{
    std::vector<std::array<double,3>> positions;
    for(int i = 0; i < satellites.size(); ++i )
    {
        std::array<double,3> position = satellites[i].computePositionECI(time);
        positions.push_back(position);
    }
    return positions;
}

std::vector<double> Simulation::getDopplerShifts(double carrierFrequency, std::array<double,3> baseStationPos)
{
    std::vector<double> dopplerShifts;
    for(int i = 0; i < satellites.size(); ++i)
    {
        double dopplerShift = satellites[i].calculateDopplerShift(carrierFrequency, baseStationPos, time);
        dopplerShifts.push_back(dopplerShift);
    }
    return dopplerShifts;
}

std::vector<Losses> Simulation::calculateLosses(double carrierFrequency, std::array<double,3> baseStationPos)
{
    std::vector<Losses> losses;
    for(int i = 0; i < satellites.size(); ++i)
    {
        Losses loss = satellites[i].calculateLosses(carrierFrequency, baseStationPos, time);
        losses.push_back(loss);
    }
    return losses;
}