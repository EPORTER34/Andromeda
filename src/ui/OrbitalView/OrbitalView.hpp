#pragma once

#include "../../util/Shapes/Shapes.hpp"
#include "../../util/Shader/Shader.hpp"

#include <vector>
#include <array>

constexpr float GL_EARTH_RADIUS = .25; //radius of the earth in screen coordinates (what gets shown to the screen)
constexpr float EARTH_EQUATORIAL_RADIUS = 6.378e6;

class OrbitalView
{
public:
    OrbitalView();
    void initializeGLBuffers();
    void render(std::vector<std::array<double,3>> satellitePositions);
    void setShaderProgram(Shader& newShader);

private:
    void initTransformationMatrices();

    Cube satellite;
    Sphere earth;
    Shader* shaderProgram;

    glm::mat4 model;    
    glm::mat4 view;    
    glm::mat4 projection;
};