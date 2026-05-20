#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

#include "../sim/Sim.hpp"
#include "../util/Spheroid/Spheroid.hpp"


class MainWindow
{
public:
    MainWindow();
    ~MainWindow();
    void run();
private:
    GLFWwindow* window;
    unsigned int compileShader(unsigned int type, const char *source);
    unsigned int createShaderProgram();
    char* vertexShaderSource;
    char* fragmentShaderSource;
    unsigned int shaderProgram;
    glm::mat4 model;    
    glm::mat4 view;    
    glm::mat4 projection;        
    GLint modelLoc;    
    GLint viewLoc;    
    GLint projLoc; 

    Spheroid earth;

    Simulation sim;

    friend void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
    friend void setSimTime(MainWindow* UI, float newTime);
};

void framebuffer_size_callback(GLFWwindow* window, int width, int height);