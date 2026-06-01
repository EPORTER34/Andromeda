#include "Doppler.hpp"

std::array<double,3> difference(std::array<double,3> minuend, std::array<double,3> subtrahend)
{
	return {minuend[0] - subtrahend[0], minuend[1] - subtrahend[1], minuend[2] - subtrahend[2]};
}

std::array<double ,3> normalize(std::array<double,3> vector)
{
	double length = sqrt(pow(vector[0],2)+pow(vector[1],2)+pow(vector[2],2));
	return {vector[0] / length, vector[1] / length, vector[2] / length };
}

double dotProduct(std::array<double,3> a, std::array<double,3> b)
{
	return a[0]*b[0] + a[1]*b[1] + a[2]*b[2];
}

double Doppler::findDopperShift(double carrierFrequency, std::array<double,3> transmitterPosECEF, 
        	     	    std::array<double,3> receiverPosECEF, std::array<double,3> satelliteVelocity)
	{
		std::array<double,3> r_hat = normalize(difference(receiverPosECEF, transmitterPosECEF));
		double v_rad = dotProduct(satelliteVelocity, r_hat);
		return carrierFrequency * v_rad / C;
	}