#include "../src/sim/LinkBudget/LinkBudget.hpp"

#include <gtest/gtest.h>


//12 Ghz is in the Sat->user band for starlink, which is used here
//6800km is the avg distance of the ISS from the earth's center, which is being used for the following tests
TEST(LinkBudgetTests, FreeSpaceLoss)
{
    double loss = LinkBudget::calculateFreeSpaceLoss(12e9, {6.378e6,0,0}, {0,6.8e6,0});
    EXPECT_NEAR(193.4225495581894, loss, 1e-9);
}

TEST(LinkBudgetTests, AtmosphericGasAborption)
{
    double loss = LinkBudget::calculateAtmosphericAbsorptionLoss(12e9, {6.378e6,0,0}, {5.888972745734182e6,3.4e6,0});
    EXPECT_NEAR(0.280867219673116, loss, 1e-9);
}