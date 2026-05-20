#include "Sim.hpp"
#include "../util/constants.hpp"

Simulation::Simulation()
{
    earthAngle = 0;
    timeStep = 1; //1 second time step
    
}

void Simulation::runTimeStep()
{
    earthAngle += EARTH_ANGULAR_VELOCITY * timeStep;
    for(int i = 0; i < satellites.size(); ++i) 
    {
        satellites[i].updatePosition(timeStep, earthAngle);
    }
}