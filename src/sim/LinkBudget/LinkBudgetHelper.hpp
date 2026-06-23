#pragma once

#include <array>

namespace LinkBudgetHelper
{
    double calculateElevationAngle(std::array<double,3> baseStationPos, std::array<double,3> satellitePos);
    double calculateRainGamma(double carrierFrequency);
};