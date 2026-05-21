#include "../src/sim/Satellite.hpp"
#include "../src/util/constants.hpp"

#include <gtest/gtest.h>

//6800km is the avg distance of the ISS from the earth's center, which is being used for the following tests
TEST(SatelliteTests, EquatorialOrbitZeroAnomaly)
{
    Satellite test(6.8e6,0,0);

    const double expected[3] = {6799995.68789,7656.66589,0.0};
    const std::array<double,3> actual = test.computePosition(1);

    for(int i = 0; i < 3; ++i) EXPECT_NEAR(actual[i],expected[i],1);
}

TEST(SatelliteTests, 45DegreeInclination45DegreeAscendingZeroAnomaly)
{
    Satellite test(6.8e6,PI/4,PI/4);

    const double expected[3] = {4804494.21216,4812150.87805,5413.58403};
    const std::array<double,3> actual = test.computePosition(1);

    for(int i = 0; i < 3; ++i) EXPECT_NEAR(actual[i],expected[i],1);
}

TEST(SatelliteTests, 60DegreeInclination30DegreeAscendingZeroAnomalyYesEarthRotation)
{
    Satellite test(6.8e6,PI/3,PI/6);

    const double expected[3] = {5890107.08789,3402882.29611,6630.00532};
    const std::array<double,3> actual = test.computePosition(1);

    for(int i = 0; i < 3; ++i) EXPECT_NEAR(actual[i],expected[i],1);
}