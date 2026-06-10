#include "OrbitalView.hpp"

OrbitalView::OrbitalView() : earth(GL_EARTH_RADIUS, {.0f,.0f,1.0f})
{

}

void OrbitalView::initializeGLBuffers()
{
    earth.initializeGLBuffers();
}

void OrbitalView::render()
{
    earth.render();
    //for(auto& i : satellites) i.render();
}