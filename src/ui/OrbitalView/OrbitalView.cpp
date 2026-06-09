#include "OrbitalView.hpp"

//earth radii:: equator: 6378km  poles: 6357km
OrbitalView::OrbitalView() : earth(6378, 6357, {.0f,.0f,1.0f })
{

}

void OrbitalView::initializeGLBuffers()
{
    earth.initializeGLBuffers();
}

void OrbitalView::render()
{
    earth.render();
}