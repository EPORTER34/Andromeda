#include "OrbitalView.hpp"

#include <iostream>

OrbitalView::OrbitalView() : earth(GL_EARTH_RADIUS, {.0f,.0f,1.0f}), satellite(GL_EARTH_RADIUS/2e1, {1.0f,0.0f,0.0f})
{
    shaderProgram = nullptr;
    initTransformationMatrices();
}

void OrbitalView::initTransformationMatrices()
{
    model = glm::mat4(1.0f);    
    view = glm::mat4(1.0f);    
    projection = glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f, -1.0f, 1.0f); 
}

void OrbitalView::initializeGLBuffers()
{
    earth.initializeGLBuffers();
    satellite.initializeGLBuffers();
}

void OrbitalView::render(std::vector<std::array<double,3>> satellitePositions)
{
    //eventually for zoom in/out
    //projection = glm::ortho(-2.0f, 2.0f, -2.0f, 2.0f, -2.0f, 2.0f);

    earth.render();

    for(int i = 0; i < satellitePositions.size(); ++i)
    {
        double posX = satellitePositions[i][1] / EARTH_EQUATORIAL_RADIUS * GL_EARTH_RADIUS;
        double posY = satellitePositions[i][2] / EARTH_EQUATORIAL_RADIUS * GL_EARTH_RADIUS;
        double posZ = satellitePositions[i][0] / EARTH_EQUATORIAL_RADIUS * GL_EARTH_RADIUS;

        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(posX, posY, posZ));
        glUniformMatrix4fv(shaderProgram->getModelLoc(), 1, GL_FALSE, glm::value_ptr(model)); 

        satellite.render();
    }

    initTransformationMatrices();
}

void OrbitalView::setShaderProgram(Shader& newShader)
{
    shaderProgram = &newShader;
}