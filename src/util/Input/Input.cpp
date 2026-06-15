#include "Input.hpp"
#include "../../ui/MainWindow.hpp"

#include <iostream>

void Input::setCallbackFunctions(GLFWwindow* window)
{
    glfwSetKeyCallback(window, keyCallback);
    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
    glfwSetScrollCallback(window, scrollCallback);
    glfwSetMouseButtonCallback(window, mouseButtonCallback);
}

void Input::framebufferSizeCallback(GLFWwindow* window, int width, int height)
{
    glViewport(0,0,width,height);
}

void Input::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    MainWindow* UI = static_cast<MainWindow*>(glfwGetWindowUserPointer(window));

    if(action == GLFW_PRESS)
    {
        switch(key)
        {
        case GLFW_KEY_ESCAPE:
            glfwSetWindowShouldClose(window, true);
            std::cout << "Simulation Terminated" << std::endl;
            break;
        case GLFW_KEY_1:
            UI->setSimSpeed(10);
            break;
        case GLFW_KEY_2:
            UI->setSimSpeed(50);
            break;
        case GLFW_KEY_3:
            UI->setSimSpeed(100);
            break;
        case GLFW_KEY_4:
            UI->setSimSpeed(500);
            break;
        case GLFW_KEY_5:
            UI->setSimSpeed(1000);
            break;
        }
    }
}

void Input::scrollCallback(GLFWwindow* window, double horzScroll, double vertScroll)
{
    MainWindow* UI = static_cast<MainWindow*>(glfwGetWindowUserPointer(window));
    if(vertScroll > 0) UI->zoomOrbitalIn();
    else UI->zoomOrbitalOut();
}

bool leftMouseHeld = false, rightMouseHeld = false; //put into namespace?
void Input::mouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_LEFT)
    {
        if (action == GLFW_PRESS)
            leftMouseHeld = true;
        else if (action == GLFW_RELEASE)
            leftMouseHeld = false;
    }
}