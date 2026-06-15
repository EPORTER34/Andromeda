#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace Input
{
    void setCallbackFunctions(GLFWwindow* window);
    
    void framebufferSizeCallback(GLFWwindow* window, int width, int height);
    void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
    void scrollCallback(GLFWwindow* window, double horzScroll, double vertScroll);
    void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
}