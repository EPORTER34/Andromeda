#pragma once

#include "../../util/constants.hpp"

#include <array>
#include <cmath>

namespace Doppler
{
    double findDopperShift(double carrierFrequency, std::array<double,3> satellitePosECEF, 
        	     	    std::array<double,3> baseStationPosECEF, std::array<double,3> satelliteVelocity);
}