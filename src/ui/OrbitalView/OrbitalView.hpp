#pragma once

#include "../../util/Shapes/Shapes.hpp"

#include <vector>

class OrbitalView
{
public:
    OrbitalView();
    void initializeGLBuffers();
    void render();
private:
    std::vector<Cube> satellites;
    Spheroid earth;
};