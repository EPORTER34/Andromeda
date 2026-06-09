#include "OrbitalView.hpp"

OrbitalView::OrbitalView() : earth(6378, {.0f,.0f,1.0f})
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