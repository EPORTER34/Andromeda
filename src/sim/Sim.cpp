#include "Sim.hpp"
#include "../util/constants.hpp"

Simulation::Simulation()
{
    time = 0;
    timeStep = 100;

}

void Simulation::runTimeStep()
{
    time += timeStep;
    for(int i = 0; i < satellites.size(); ++i)
    {
        satellites[i].computePosition(time);
    }
}

void Simulation::setTimeStep(float newTimeStep)
{
    timeStep = newTimeStep;
}