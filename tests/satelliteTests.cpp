#include "../src/sim/Satellite.hpp"
#include "../src/util/constants.hpp"

#include <gtest/gtest.h>

#include <iostream>


//6800km is the avg distance of the ISS from the earth's center, which is being used for the following tests
TEST(SatelliteTests, EquatorialOrbitZeroAnomaly)
{
    Satellite test(6.8e6,0,0);
    test.updatePosition(1, 0);

    const float expected[3] = {6.79999569e6,7.655984675e3,0};
    const float* actual = test.getPosition();

    for(int i = 0; i < 3; ++i) EXPECT_NEAR(actual[i],expected[i],.01);
}

TEST(SatelliteTests, 45DegreeInclinationZeroAnomaly)
{
    Satellite test(6.8e6,PI/4,0);
    test.updatePosition(1, 0);

    const float expected[3] = {6.79999569e6,5.413598681e3,5.41359868e3};
    const float* actual = test.getPosition();

    for(int i = 0; i < 3; ++i) EXPECT_NEAR(actual[i],expected[i],.01);
}

TEST(SatelliteTests, PolarOrbitZeroAnomaly)
{
    Satellite test(6.8e6,PI/2,0);
    test.updatePosition(1, 0);

    const float expected[3] = {6.79999569e6,0,7.655984675e3};
    const float* actual = test.getPosition();

    for(int i = 0; i < 3; ++i) EXPECT_NEAR(actual[i],expected[i],.01);
}