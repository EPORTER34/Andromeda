#include "../Orbit/Orbit.hpp"

#include <array>

class Satellite
{
public:
    Satellite(double newRadius, double newInclination, double newAscendingLongitude, double newAnomaly);
    std::array<double, 3> computePosition(double simulationTime) const;
    std::array<double, 3> computeVelocity(double simulationtime) const;
    //double calculateDopplerShift(double carrierFrequency) const;
private:
    Orbit orbit;
};