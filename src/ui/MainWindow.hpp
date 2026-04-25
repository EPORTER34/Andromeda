#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

class MainWindow
{
public:
    MainWindow();
    ~MainWindow();
    void run();
private:
    GLFWwindow* window;
};

void framebuffer_size_callback(GLFWwindow* window, int width, int height);