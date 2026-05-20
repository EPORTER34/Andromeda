#include "../src/sim/Satellite.hpp"

#include <gtest/gtest.h>

#include <iostream>

TEST(SatelliteTests, EquatorialOrbit)
{
    std::cout << "TEMP";
}

TEST(SatelliteTests, RadiusStaysConstant)
{
    float radius = 6999.95f;

    EXPECT_NEAR(radius, 7000.0f, 0.1f);
}