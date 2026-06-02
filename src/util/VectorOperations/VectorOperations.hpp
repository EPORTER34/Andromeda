#pragma once
#include <array>

namespace VecOps
{
    std::array<double,3> difference(std::array<double,3> minuend, std::array<double,3> subtrahend);
    std::array<double ,3> normalize(std::array<double,3> vector);
    double dotProduct(std::array<double,3> a, std::array<double,3> b);
    std::array<double,3> crossProduct(std::array<double,3> a, std::array<double,3> b);
    std::array<double,3> distributeConstant(std::array<double,3> vec, double constant);
}