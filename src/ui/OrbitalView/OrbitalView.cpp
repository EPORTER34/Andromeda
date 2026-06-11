#include "OrbitalView.hpp"

#include <iostream>

OrbitalView::OrbitalView() : earth(GL_EARTH_RADIUS, {.0f,.0f,1.0f}), satellite(GL_EARTH_RADIUS/2e1, {1.0f,0.0f,0.0f})
{
    
}

void OrbitalView::initializeGLBuffers()
{
    earth.initializeGLBuffers();
    satellite.initializeGLBuffers();
}

void OrbitalView::render(std::vector<std::array<double,3>> satellitePositions)
{
    earth.render();
    satellite.render(); //TODO: move to loop & add a input condition for the center position to shift to
    for(int i = 0; i < satellitePositions.size(); ++i)
    {

        //std::cout << "X: " << satellitePositions[i][0] << " Y: " << satellitePositions[i][1] << " Z: " << satellitePositions[i][2] << std::endl;

        //TODO: use the positions one by one to move cubes (or 1 cube if possible)
        //      to render satellites to the screen, (use i to increment through the array)
        //      math: GL_EARTH_RADIUS * position / EARTH_EQUATORIAL_RADIUS
    }
}