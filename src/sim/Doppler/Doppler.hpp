#pragma once

#include "../../util/constants.hpp"

#include <array>
#include <cmath>

namespace Doppler
{
    double findDopperShift(double carrierFrequency, std::array<double,3> transmitterPosECEF, 
        	     	    std::array<double,3> receiverPosECEF, std::array<double,3> satelliteVelocity);
}