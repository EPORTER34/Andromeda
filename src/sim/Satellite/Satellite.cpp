#include "Satellite.hpp"
#include "../Doppler/Doppler.hpp"

Satellite::Satellite(double newRadius, double newInclination, double newAscendingLongitude, double newAnomaly)
 :orbit(newRadius,newInclination,newAscendingLongitude,newAnomaly)
{
    //probally need to put something here later
}

std::array<double, 3> Satellite::computePosition(double simulationTime) const
{
    return orbit.computePosition(simulationTime);
}
std::array<double, 3> Satellite::computeVelocity(double simulationtime) const
{
    return orbit.computeVelocity(simulationtime);
}

//double Satellite::calculateDopplerShift(double carrierFrequency, std::array<double,3> ) const
//{
//    Doppler::findDopperShift(carrierFrequency)
//}