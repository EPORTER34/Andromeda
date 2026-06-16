#include "../Orbit/Orbit.hpp"
#include "../LinkBudget/LinkBudget.hpp"

#include <array>
#include <string>

class Satellite
{
public:
    Satellite(std::string newName, double newRadius, double newInclination, double newAscendingLongitude, double newAnomaly);
    std::array<double, 3> computePositionECI(double simulationTime) const;
    std::array<double, 3> computeVelocity(double simulationtime) const;

    double calculateDopplerShift(double carrierFrequency, std::array<double,3> baseSationPositionECEF, double simTime) const;

private:
    Orbit orbit;
    std::string name;
};