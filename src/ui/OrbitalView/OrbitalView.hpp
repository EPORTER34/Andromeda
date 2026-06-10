#pragma once

#include "../../util/Shapes/Shapes.hpp"

#include <vector>

constexpr float GL_EARTH_RADIUS = .25; //radius of the earth in screen coordinates (what gets shown to the screen)

class OrbitalView
{
public:
    OrbitalView();
    void initializeGLBuffers();
    void render();
private:
    std::vector<Cube> satellites;
    Sphere earth;
};