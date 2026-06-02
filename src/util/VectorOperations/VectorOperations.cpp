#include "VectorOperations.hpp"

#include <cmath>

std::array<double,3> VecOps::difference(std::array<double,3> minuend, std::array<double,3> subtrahend)
{
	return {minuend[0] - subtrahend[0], minuend[1] - subtrahend[1], minuend[2] - subtrahend[2]};
}

std::array<double ,3> VecOps::normalize(std::array<double,3> vector)
{
	double length = sqrt(pow(vector[0],2)+pow(vector[1],2)+pow(vector[2],2));
	return {vector[0] / length, vector[1] / length, vector[2] / length };
}

double VecOps::dotProduct(std::array<double,3> a, std::array<double,3> b)
{
	return a[0]*b[0] + a[1]*b[1] + a[2]*b[2];
}

std::array<double,3> VecOps::crossProduct(std::array<double,3> a, std::array<double,3> b)
{
    double x = a[2]*b[3] - a[3]*b[2],
    y = a[3]*b[1] - a[1]*b[3],
    z = a[1]*b[2] - a[2]*b[1];
    return {x,y,z};
}

std::array<double,3> distributeConstant(std::array<double,3> vec, double constant)
{
    return {vec[0] * constant, vec[1] * constant, vec[2] * constant};
}