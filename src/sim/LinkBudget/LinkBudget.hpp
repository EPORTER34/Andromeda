#pragma once

#include <array>

class Losses
{
public:
    void sumLosses();

    double totalLoss;
    double freeSpaceLoss;
    double atmosphericAbsorptionLoss;
};

namespace LinkBudget
{
    Losses calculateLosses(double carrierFrequency, std::array<double,3> baseStationPos, std::array<double,3> satellitePos);
    double calculateFreeSpaceLoss(double carrierFrequency, std::array<double,3> baseStationPos, std::array<double,3> satellitePos);
    double calculateAtmosphericAbsorptionLoss(double carrierFrequency, std::array<double,3> baseStationPos, std::array<double,3> satellitePos);
}