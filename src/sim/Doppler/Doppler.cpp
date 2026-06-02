#include "Doppler.hpp"
#include "../../util/VectorOperations/VectorOperations.hpp"

double Doppler::findDopperShift(double carrierFrequency, std::array<double,3> transmitterPosECEF, 
        	     	    std::array<double,3> receiverPosECEF, std::array<double,3> satelliteVelocity)
	{
		std::array<double,3> r = VecOps::difference(receiverPosECEF, transmitterPosECEF);
		std::array<double,3> r_hat = VecOps::normalize(r);
		double v_rad = VecOps::dotProduct(satelliteVelocity, r_hat);
		return carrierFrequency * v_rad / C;
	}