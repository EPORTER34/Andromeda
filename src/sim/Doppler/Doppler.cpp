#include "Doppler.hpp"
#include "../../util/VectorOperations/VectorOperations.hpp"

double Doppler::findDopperShift(double carrierFrequency, std::array<double,3> satellitePosECEF, 
        	     	    std::array<double,3> baseStationPosECEF, std::array<double,3> satelliteVelocity)
	{
		std::array<double,3> r = VecOps::difference(baseStationPosECEF, satellitePosECEF);
		std::array<double,3> r_hat = VecOps::normalize(r);
		double v_rad = VecOps::dotProduct(satelliteVelocity, r_hat);
		return carrierFrequency * v_rad / C;
	}