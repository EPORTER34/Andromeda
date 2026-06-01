#include "../src/sim/Doppler/Doppler.hpp"
#include "../src/util/constants.hpp"

#include <gtest/gtest.h>

#include <array>
#include <cmath>

//12 Ghz is in the Sat->user band for starlink, which is used here
//6800km is the avg distance of the ISS from the earth's center, which is being used for the following tests
TEST(DopplerTests, SatDirectlyAboveGroundstation)
{
    double shiftAmount = Doppler::findDopperShift(12e9,{6378,0,0},{6800,0,0},{0,sqrt(MU_EARTH/6.8e6),0});
    EXPECT_NEAR(0, shiftAmount, 1e-3);
}

//TODO: finish this test
TEST(DopplerTests, 60DegreeInclination30DegreeAscending45DegreeAnomaly)
{
    double vel = sqrt(MU_EARTH/6.8e6);
    double shiftAmount = Doppler::findDopperShift(12e9,{6378,0,0},{},{0,0,0});
    EXPECT_NEAR(0, shiftAmount, 1e-3);
}