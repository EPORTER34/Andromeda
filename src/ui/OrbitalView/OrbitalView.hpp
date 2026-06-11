#pragma once

#include "../../util/Shapes/Shapes.hpp"

#include <vector>
#include <array>

constexpr float GL_EARTH_RADIUS = .25; //radius of the earth in screen coordinates (what gets shown to the screen)
constexpr float EARTH_EQUATORIAL_RADIUS = 6378;

class OrbitalView
{
public:
    OrbitalView();
    void initializeGLBuffers();
    void render(std::vector<std::array<double,3>> satellitePositions);

private:
    Cube satellite;
    Sphere earth;
};