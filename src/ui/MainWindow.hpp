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
    void processInput();
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
};

void framebuffer_size_callback(GLFWwindow* window, int width, int height);