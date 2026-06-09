#pragma once

#include "../../util/Shapes/Shapes.hpp"

class OrbitalView
{
public:
    OrbitalView();
    void initializeGLBuffers();
    void render();
private:

    Spheroid earth;
};