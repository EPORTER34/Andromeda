#pragma once

#include <array>

class Losses
{
public:
    double totalLoss;
    double freeSpaceLoss;
    double atmosphericAbsorptionLoss;
    double rainLoss;
};

namespace LinkBudget
{
    Losses calculateLosses(double carrierFrequency, std::array<double,3> baseStationPos, std::array<double,3> satellitePos);
    double calculateFreeSpaceLoss(double carrierFrequency, std::array<double,3> baseStationPos, std::array<double,3> satellitePos);
    double calculateAtmosphericAbsorptionLoss(double carrierFrequency, double elevationAngle);
    double calculateRainLoss(double carrierFrequency, double elevationAngle);
}