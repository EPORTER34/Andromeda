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

private:
    void createGLWindow();
    void checkWindowLoaded();
    void checkGladLoaded();
    void setWindowAttributes();

    void initTransformationMatrices();

    GLFWwindow* window;
    Shader shader;

    glm::mat4 model;    
    glm::mat4 view;    
    glm::mat4 projection;

    OrbitalView orbitalView;

    Simulation sim;
};

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);