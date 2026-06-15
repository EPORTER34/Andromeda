#include "Satellite.hpp"
#include "../Doppler/Doppler.hpp"

Satellite::Satellite(std::string newName, double newRadius, double newInclination, double newAscendingLongitude, double newAnomaly)
 :orbit(newRadius,newInclination,newAscendingLongitude,newAnomaly)
{
    name = newName;
}

std::array<double, 3> Satellite::computePositionECI(double simulationTime) const
{
    return orbit.computePositionECI(simulationTime);
}
std::array<double, 3> Satellite::computeVelocity(double simulationtime) const
{
    return orbit.computeVelocity(simulationtime);
}

double Satellite::calculateDopplerShift(double carrierFrequency, std::array<double,3> baseSationPositionECEF, double simTime) const
{
    std::array<double,3> satPos = orbit.computePositionECEF(simTime);
    std::array<double,3> satVel = orbit.computeVelocity(satPos);
    return Doppler::findDopperShift(carrierFrequency, satPos, baseSationPositionECEF, satVel);
}