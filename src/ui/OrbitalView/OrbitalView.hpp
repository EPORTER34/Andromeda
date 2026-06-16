#pragma once

#include "../../util/Shapes/Shapes.hpp"
#include "../../util/Shader/Shader.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <vector>
#include <array>

constexpr float GL_EARTH_RADIUS = .25; //radius of the earth in screen coordinates (what gets shown to the screen)
constexpr float ROTATE_SENSITIVITY = 1e0;
constexpr float EARTH_EQUATORIAL_RADIUS = 6.378e6;

class OrbitalView
{
public:
    OrbitalView();
    void initializeGLBuffers();
    void render(std::vector<std::array<double,3>> satellitePositions);
    void setShaderProgram(Shader& newShader);
    void zoomIn();
    void zoomOut();
    void rotateLeftRight(double deltaX);
    void rotateUpDown(double deltaY);
    void resizeWindow(int width, int height);

private:
    void initTransformationMatrices();
    void calculateCameraPosition();
    void renderSatellites(std::vector<std::array<double,3>> satellitePositions);
    void calculateSatModel(std::array<double,3> position);

    Cube satellite;
    Sphere earth;
    Shader* shaderProgram;

    glm::mat4 model;    
    glm::mat4 view;    
    glm::mat4 projection;

    //TODO: maybe move these into a zoom class under util
    float yaw, pitch, distance;
    glm::vec3 cameraPos;
};