#include "VectorOperations.hpp"

#include <cmath>

constexpr short int X = 0;
constexpr short int Y = 1;
constexpr short int Z = 2;

std::array<double,3> VecOps::difference(std::array<double,3> minuend, std::array<double,3> subtrahend)
{
	return {minuend[X] - subtrahend[X], minuend[Y] - subtrahend[Y], minuend[Z] - subtrahend[Z]};
}

double VecOps::magnitude(std::array<double,3> vector)
{
    return sqrt(pow(vector[X],2) + pow(vector[Y],2) + pow(vector[Z],2));
}

std::array<double ,3> VecOps::normalize(std::array<double,3> vector)
{
	double length = magnitude(vector);
	return {vector[X] / length, vector[Y] / length, vector[Z] / length };
}

double VecOps::dotProduct(std::array<double,3> a, std::array<double,3> b)
{
	return a[X]*b[X] + a[Y]*b[Y] + a[Z]*b[Z];
}

std::array<double,3> VecOps::crossProduct(std::array<double,3> a, std::array<double,3> b)
{
    double x = a[Y]*b[Z] - a[Z]*b[Y],
    y = a[Z]*b[X] - a[X]*b[Z],
    z = a[X]*b[Y] - a[Y]*b[X];
    return {x,y,z};
}

std::array<double,3> VecOps::distributeConstant(std::array<double,3> vec, double k)
{
    return {vec[X] * k, vec[Y] * k, vec[Z] * k};
}