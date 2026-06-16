#include "OrbitalView.hpp"

#include <iostream>
#include <cmath>

OrbitalView::OrbitalView() : earth(GL_EARTH_RADIUS, {.0f,.0f,1.0f}), satellite(GL_EARTH_RADIUS/2e1, {1.0f,0.0f,0.0f})
{
    shaderProgram = nullptr;
    initTransformationMatrices();
    yaw = 90;
    pitch = 0;
    distance = 5 * GL_EARTH_RADIUS;
}

void OrbitalView::initTransformationMatrices()
{
    model = glm::mat4(1.0f);    
    view = glm::mat4(1.0f);    
    //width/height   TODO: make this change projection on resize of window
    projection = glm::perspective(glm::radians(60.0f), (float)1000 / (float)1000, 0.01f, 100000.0f);
}

void OrbitalView::initializeGLBuffers()
{
    earth.initializeGLBuffers();
    satellite.initializeGLBuffers();
}

void OrbitalView::render(std::vector<std::array<double,3>> satellitePositions)
{
    glUniformMatrix4fv(shaderProgram->getProjLoc(), 1, GL_FALSE, glm::value_ptr(projection));

    calculateCameraPosition();
    view = glm::lookAt(cameraPos, glm::vec3(0.0f), glm::vec3(0, 1, 0));
    glUniformMatrix4fv(shaderProgram->getViewLoc(), 1, GL_FALSE, glm::value_ptr(view)); 
    
    for(int i = 0; i < satellitePositions.size(); ++i)
    {
        calculateSatModel(satellitePositions[i]);
        glUniformMatrix4fv(shaderProgram->getModelLoc(), 1, GL_FALSE, glm::value_ptr(model)); 

        satellite.render();
    }
    model = glm::mat4(1.0f); 
    glUniformMatrix4fv(shaderProgram->getModelLoc(), 1, GL_FALSE, glm::value_ptr(model)); 

    earth.render();

    initTransformationMatrices();
    glUniformMatrix4fv(shaderProgram->getViewLoc(), 1, GL_FALSE, glm::value_ptr(view)); 
}

void OrbitalView::calculateCameraPosition()
{
    cameraPos.x = distance * cos(glm::radians(pitch)) * cos(glm::radians(yaw));
    cameraPos.y = distance * sin(glm::radians(pitch));
    cameraPos.z = distance * cos(glm::radians(pitch)) * sin(glm::radians(yaw));
}

void OrbitalView::calculateSatModel(std::array<double,3> position)
{
    double posX = position[1] / EARTH_EQUATORIAL_RADIUS * GL_EARTH_RADIUS;
    double posY = position[2] / EARTH_EQUATORIAL_RADIUS * GL_EARTH_RADIUS;
    double posZ = position[0] / EARTH_EQUATORIAL_RADIUS * GL_EARTH_RADIUS;

    model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(posX, posY, posZ));
}

void OrbitalView::setShaderProgram(Shader& newShader)
{
    shaderProgram = &newShader;
}

void OrbitalView::zoomIn()
{
    if(distance > 3 * GL_EARTH_RADIUS) distance -= .1f;
}

void OrbitalView::zoomOut()
{
    if(distance < 20 * GL_EARTH_RADIUS) distance += .1f;
}

void OrbitalView::rotateLeftRight(double deltaX)
{
    yaw += deltaX * ROTATE_SENSITIVITY;
}

void OrbitalView::rotateUpDown(double deltaY)
{
    pitch += deltaY * ROTATE_SENSITIVITY;
    if(pitch > 89.9) pitch = 89.9;
    if(pitch < -89.9) pitch = -89.9;
}