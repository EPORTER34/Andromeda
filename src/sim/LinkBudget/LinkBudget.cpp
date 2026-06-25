#include "LinkBudget.hpp"
#include "../../util/constants.hpp"
#include "../../util/VectorOperations/VectorOperations.hpp"
#include "LinkBudgetHelper.hpp"

#include <cmath>

Losses LinkBudget::calculateLosses(double carrierFrequency, std::array<double,3> baseStationPos, std::array<double,3> satellitePos)
{
    Losses losses;
    losses.freeSpaceLoss = calculateFreeSpaceLoss(carrierFrequency, baseStationPos, satellitePos);

    double elevationAngle = LinkBudgetHelper::calculateElevationAngle(baseStationPos, satellitePos);
    losses.atmosphericAbsorptionLoss = calculateAtmosphericAbsorptionLoss(carrierFrequency, elevationAngle);
    losses.rainLoss = calculateRainLoss(carrierFrequency, elevationAngle);

    losses.totalLoss = LinkBudgetHelper::sumLosses(losses);
    return losses;
}

constexpr double FREE_SPACE_CONST = 4 * PI / C;
double LinkBudget::calculateFreeSpaceLoss(double carrierFrequency, std::array<double,3> baseStationPos, std::array<double,3> satellitePos)
{
    std::array<double,3> displacement = VecOps::difference(baseStationPos, satellitePos);
    double distance = VecOps::magnitude(displacement);
    return 20 * log10(FREE_SPACE_CONST * distance * carrierFrequency);
}

constexpr double atmsphereThick = 8; //effective atmosphere thickness [km]
double LinkBudget::calculateAtmosphericAbsorptionLoss(double carrierFrequency, double elevationAngle)
{
    double fGHz = carrierFrequency / 1e9;
    double f2 = fGHz * fGHz;
    double surfaceAttenuation = .002 * f2 / (f2 + 25) + .0035 * f2 / (f2 + 9);

    return surfaceAttenuation * atmsphereThick / sin(elevationAngle);
}

constexpr double rainThick = 4; //effective rain thickness [km]
double LinkBudget::calculateRainLoss(double carrierFrequency, double elevationAngle)
{
    double gamma = LinkBudgetHelper::calculateRainGamma(carrierFrequency);
    return gamma * rainThick / sin(elevationAngle);
}