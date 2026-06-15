#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../sim/Sim.hpp"
#include "OrbitalView/OrbitalView.hpp"
#include "../util/Shader/Shader.hpp"

class MainWindow
{
public:
    MainWindow();
    ~MainWindow();
    void run();
    void setSimSpeed(float newSpeed);
    void zoomOrbitalIn();
    void zoomOrbitalOut();

private:
    void createGLWindow();
    void checkWindowLoaded();
    void checkGladLoaded();
    void setWindowAttributes();

    void initTransformationMatrices();

    void loadNetworkFromCSV(std::string filePath);
    
    GLFWwindow* window;
    Shader shader;

    glm::mat4 model;    
    glm::mat4 view;    
    glm::mat4 projection;

    OrbitalView orbitalView;

    Simulation sim;
};