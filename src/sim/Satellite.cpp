#include "Satellite.hpp"
#include "../util/constants.hpp"

#include <cmath>

Satellite::Satellite(std::initializer_list<float> initialPosition, float orbitalRadius)
{
    centripAccel = G * MASS_EARTH / pow(orbitalRadius,2);  //g = a_c = G*M/r^2
    float magVel = sqrt(centripAccel*orbitalRadius);       //v = sqrt(g*r)




    for(int i = 0; i < 3; i++) position[i] = initialPosition.begin()[i];
}