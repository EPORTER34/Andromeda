#include "../src/sim/Orbit/Orbit.hpp"
#include "../src/util/constants.hpp"

#include <gtest/gtest.h>

#include <array>

//6800km is the avg distance of the ISS from the earth's center, which is being used for the following tests
TEST(OrbitTests, EquatorialOrbit)
{
    OrbitalElements orbit(6.8e6,0,0,0);
    Orbit test(orbit);

    const double expected[3] = { 6799996.22811, 7160.80242, 0.0};
    const std::array<double,3> actual = test.computePositionECEF(1.0);

    for(int i = 0; i < 3; ++i) EXPECT_NEAR(actual[i],expected[i],1);
}

TEST(OrbitTests, ArbitrarySymmetricOrbit)
{
    OrbitalElements orbit(6.8e6,PI/4,PI/4,0);
    Orbit test(orbit);

    const double expected[3] = {4804845.08459, 4811800.53790, 5413.58403};
    const std::array<double,3> actual = test.computePositionECEF(1);

    for(int i = 0; i < 3; ++i) EXPECT_NEAR(actual[i],expected[i],1);
}

TEST(OrbitTests, ArbitraryAsymmetricOrbit)
{
    OrbitalElements orbit(6.8e6,PI/3,PI/6,0);
    Orbit test(orbit);

    const double expected[3] = {5.887303116222798e6,3.402883785034083e6,0.006630480031255e6};
    const std::array<double,3> actual = test.computePositionECEF(1);

    for(int i = 0; i < 3; ++i) EXPECT_NEAR(actual[i],expected[i],1);
}


TEST(OrbitTests, VelocityFlatOrbit)
{
    OrbitalElements orbit(6.8e6,0,0,0);
    Orbit test(orbit);
     std::array<double,3> position = {6.8e6,0,0};

    const double expected[3] = {0,7656.220479414877,0};
    const std::array<double,3> actual = test.computeVelocity(position);

    for(int i = 0; i < 3; ++i) EXPECT_NEAR(actual[i],expected[i],1);
}

TEST(OrbitTests, VelocityGivenPosition)
{
    OrbitalElements orbit(6.8e6,PI/3,PI/6,0);
    Orbit test(orbit);
    std::array<double,3> position = {5.887303116222798e6,3.402883785034083e6,0.006630480031255e6};

    const std::array<double,3> expected = {-1910.079551363330,3317.533379535403,6630.477484032930};
    const std::array<double,3> actual = test.computeVelocity(position);

    for(int i = 0; i < 3; ++i) EXPECT_NEAR(actual[i],expected[i],1);
}