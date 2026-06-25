#include "LinkBudgetHelper.hpp"
#include "../../util/VectorOperations/VectorOperations.hpp"

#include <cmath>

double LinkBudgetHelper::sumLosses(const Losses& losses)
{
    double totalLoss = losses.freeSpaceLoss;
    totalLoss += losses.atmosphericAbsorptionLoss;
    totalLoss += losses.rainLoss;
    return totalLoss;
}

double LinkBudgetHelper::calculateElevationAngle(std::array<double,3> baseStationPos, std::array<double,3> satellitePos)
{
    std::array<double,3> unitDisplacement = VecOps::normalize(VecOps::difference(satellitePos, baseStationPos));
    std::array<double,3> unitBasePos = VecOps::normalize(baseStationPos);
    double sinElevationAngle = VecOps::dotProduct(unitDisplacement, unitBasePos); 
    if(sinElevationAngle < 0) sinElevationAngle *= -1; 
    return asin(sinElevationAngle);
}

constexpr double rainRate = 100; //rain rate [mm/hr]
double LinkBudgetHelper::calculateRainGamma(double carrierFrequency)
{
    double alpha = 0, k = 0;
    double fGHz = carrierFrequency / 1e9;
    if(fGHz >= 40)
    {
        alpha = .9 - .005 * (fGHz - 40);
        k = .4 + .025 * (fGHz - 40);
    }
    else if (fGHz >= 30)
    {
        alpha = .95 - .005 * (fGHz - 30);
        k = .22 + .018 * (fGHz - 30);
    }
    else if (fGHz >= 20)
    {
        alpha = 1.05 - .01 * (fGHz - 20);
        k = .075 + .0145 * (fGHz - 20);
    }
    else if (fGHz >= 14)
    {
        alpha = 1.1 - .00833 * (fGHz - 14);
        k = .035 + .006667 * (fGHz - 14);
    }
    else if (fGHz >= 12)
    {
        alpha = 1.2 - .05 * (fGHz - 12);
        k = .018 + .0085 * (fGHz - 12);
    }
    else if (fGHz >= 10)
    {
        alpha = 1.25 - .025 * (fGHz - 10);
        k = .012 + .003 * (fGHz - 10);
    }
    else if (fGHz >= 6)
    {
        alpha = 1 + .0625 * (fGHz - 6);
        k = .0005 + .002875 * (fGHz - 6);
    }
    else if (fGHz >= 4)
    {
        alpha = 1.0;
        k = .0001 + .0002 * (fGHz - 4);
    }
    return k * pow(rainRate, alpha);
}