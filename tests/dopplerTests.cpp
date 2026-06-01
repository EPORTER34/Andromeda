#include "../src/sim/Doppler/Doppler.hpp"
#include "../src/util/constants.hpp"

#include <gtest/gtest.h>

#include <array>
#include <cmath>

//12 Ghz is in the Sat->user band for starlink, which is used here
//6800km is the avg distance of the ISS from the earth's center, which is being used for the following tests
TEST(DopplerTests, SatDirectlyAboveGroundstation)
{
    double shiftAmount = Doppler::findDopperShift(12e9,{6.8e6,0,0},{6.378e6,0,0},{0,sqrt(MU_EARTH/6.8e6),0});
    EXPECT_NEAR(0, shiftAmount, 1e-9);
}

TEST(DopplerTests, ArbitraryOrbit)
{
    std::array<double,3> position = {2962051034.714272,4486229337.399963,4164132562.731402};
    std::array<double,3> velocity = {-4.555717982834315e+03,-3.626535180251327e+02,3.631300346230551e+03};
    double shiftAmount = Doppler::findDopperShift(12e9,position,{6.378e6,0,0},velocity);
    EXPECT_NEAR(-171.1079921252320, shiftAmount, 1e-9);
}

TEST(DopplerTests, MaxApproachingDoppler)
{
    //NOTE: this is not an orbit, simply a line with the sat directly approaching the receiver
    //std::array<double,3> position = {2962051034.714272,4486229337.399963,4164132562.731402};
    //std::array<double,3> velocity = {-4.555717982834315e+03,-3.626535180251327e+02,3.631300346230551e+03};
    double shiftAmount = Doppler::findDopperShift(12e9,{6.8e6,0,0},{0,0,0},{-7500,0,0});
    EXPECT_NEAR(300207.6856783368, shiftAmount, 1e-9);
}