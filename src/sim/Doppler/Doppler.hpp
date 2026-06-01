#pragma once
#include <array>

namespace Doppler
{
    double findDopperShift(double carrierFrequency, std::array<double,3> transmitterPosECEF, 
        	     	    std::array<double,3> receiverPosECEF, std::array<double,3> satelliteVelocity);
}