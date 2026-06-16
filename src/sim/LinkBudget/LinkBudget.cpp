#include "LinkBudget.hpp"
#include "../../util/constants.hpp"

#include <cmath>

Losses LinkBudget::calculateLosses(double carrierFrequency, std::array<double,3> baseStationPos, std::array<double,3> satellitePos)
{
    Losses losses;
    losses.freeSpaceLoss = calculateFreeSpaceLoss(carrierFrequency, baseStationPos, satellitePos);

    return losses;
}

constexpr double FREE_SPACE_CONST = 4 * PI / C;
double LinkBudget::calculateFreeSpaceLoss(double carrierFrequency, std::array<double,3> baseStationPos, std::array<double,3> satellitePos)
{
    double deltaX = baseStationPos[0] - satellitePos[0];
    double deltaY = baseStationPos[1] - satellitePos[1];
    double deltaZ = baseStationPos[2] - satellitePos[2];
    double distance = sqrt(pow(deltaX,2) + pow(deltaY,2) + pow(deltaZ,2));

    return 20 * log10(FREE_SPACE_CONST * distance * carrierFrequency);
}