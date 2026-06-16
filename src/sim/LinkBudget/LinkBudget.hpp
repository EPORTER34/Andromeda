#pragma once

#include <array>

class Losses
{
public:
    double totalLoss;
    double freeSpaceLoss;
};

namespace LinkBudget
{
    Losses calculateLosses(double carrierFrequency, std::array<double,3> baseStationPos, std::array<double,3> satellitePos);
    double calculateFreeSpaceLoss(double carrierFrequency, std::array<double,3> baseStationPos, std::array<double,3> satellitePos);
}