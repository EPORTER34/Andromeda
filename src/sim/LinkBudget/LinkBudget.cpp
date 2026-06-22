#include "LinkBudget.hpp"
#include "../../util/constants.hpp"
#include "../../util/VectorOperations/VectorOperations.hpp"

#include <cmath>

void Losses::sumLosses()
{
    totalLoss += freeSpaceLoss;
    totalLoss += atmosphericAbsorptionLoss;
    totalLoss += rainLoss;
}

Losses LinkBudget::calculateLosses(double carrierFrequency, std::array<double,3> baseStationPos, std::array<double,3> satellitePos)
{
    Losses losses;
    losses.freeSpaceLoss = calculateFreeSpaceLoss(carrierFrequency, baseStationPos, satellitePos);
    losses.atmosphericAbsorptionLoss = calculateAtmosphericAbsorptionLoss(carrierFrequency, baseStationPos, satellitePos);

    losses.sumLosses();
    return losses;
}

constexpr double FREE_SPACE_CONST = 4 * PI / C;
double LinkBudget::calculateFreeSpaceLoss(double carrierFrequency, std::array<double,3> baseStationPos, std::array<double,3> satellitePos)
{
    std::array<double,3> displacement = VecOps::difference(baseStationPos, satellitePos);
    double distance = VecOps::magnitude(displacement);
    return 20 * log10(FREE_SPACE_CONST * distance * carrierFrequency);
}

constexpr double L_EFF = 8; //effective atmosphere thickness [km]
double LinkBudget::calculateAtmosphericAbsorptionLoss(double carrierFrequency, std::array<double,3> baseStationPos, std::array<double,3> satellitePos)
{
    double fGHz = carrierFrequency / 1e9;
    double f2 = fGHz * fGHz;
    double surfaceAttenuation = .002 * f2 / (f2 + 25) + .0035 * f2 / (f2 + 9);


    //calculate elevation angle function
    std::array<double,3> unitDisplacement = VecOps::normalize(VecOps::difference(satellitePos, baseStationPos));
    std::array<double,3> unitBasePos = VecOps::normalize(baseStationPos);
    double sinElevationAngle = VecOps::dotProduct(unitDisplacement, unitBasePos); 
    if(sinElevationAngle < 0) sinElevationAngle *= -1;

    return surfaceAttenuation * L_EFF / sinElevationAngle;
}

double LinkBudget::calculateRainLoss(double carrierFrequency, std::array<double,3> baseStationPos, std::array<double,3> satellitePos)
{
    //calculate gamma function


    //calculate elevation angle function
    std::array<double,3> unitDisplacement = VecOps::normalize(VecOps::difference(satellitePos, baseStationPos));
    std::array<double,3> unitBasePos = VecOps::normalize(baseStationPos);
    double sinElevationAngle = VecOps::dotProduct(unitDisplacement, unitBasePos); 
    if(sinElevationAngle < 0) sinElevationAngle *= -1;

    //scaling path length by elevation angle

    //return gamma * path length
}