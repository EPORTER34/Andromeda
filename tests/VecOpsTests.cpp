#include "../src/util/VectorOperations/VectorOperations.hpp"

#include <gtest/gtest.h>

constexpr double EPSILON = 1e-9;

TEST(VecOpsTest, Difference)
{
    std::array<double,3> a{5.0, 7.0, 9.0};
    std::array<double,3> b{1.0, 2.0, 3.0};

    auto result = VecOps::difference(a, b);

    EXPECT_DOUBLE_EQ(result[0], 4.0);
    EXPECT_DOUBLE_EQ(result[1], 5.0);
    EXPECT_DOUBLE_EQ(result[2], 6.0);
}

TEST(VecOpsTest, Magnitude)
{
    std::array<double,3> vec{3.0, 4.0, 12.0};

    double result = VecOps::magnitude(vec);

    EXPECT_NEAR(result, 13.0, EPSILON);
}

TEST(VecOpsTest, Normalize)
{
    std::array<double,3> vec{3.0, 0.0, 4.0};

    auto result = VecOps::normalize(vec);

    EXPECT_NEAR(result[0], 0.6, EPSILON);
    EXPECT_NEAR(result[1], 0.0, EPSILON);
    EXPECT_NEAR(result[2], 0.8, EPSILON);

    EXPECT_NEAR(VecOps::magnitude(result), 1.0, EPSILON);
}

TEST(VecOpsTest, DotProduct)
{
    std::array<double,3> a{1.0, 2.0, 3.0};
    std::array<double,3> b{4.0, -5.0, 6.0};

    double result = VecOps::dotProduct(a, b);

    EXPECT_DOUBLE_EQ(result, 12.0);
    // 1*4 + 2*(-5) + 3*6 = 4 - 10 + 18 = 12
}

TEST(VecOpsTest, CrossProduct)
{
    std::array<double,3> a{1.0, 0.0, 0.0};
    std::array<double,3> b{0.0, 1.0, 0.0};

    auto result = VecOps::crossProduct(a, b);

    EXPECT_DOUBLE_EQ(result[0], 0.0);
    EXPECT_DOUBLE_EQ(result[1], 0.0);
    EXPECT_DOUBLE_EQ(result[2], 1.0);
}

TEST(VecOpsTest, DistributeConstant)
{
    std::array<double,3> vec{1.0, -2.0, 3.0};

    auto result = VecOps::distributeConstant(vec, 2.5);

    EXPECT_DOUBLE_EQ(result[0], 2.5);
    EXPECT_DOUBLE_EQ(result[1], -5.0);
    EXPECT_DOUBLE_EQ(result[2], 7.5);
}