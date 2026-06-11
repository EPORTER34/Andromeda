#include "MainWindow.hpp"

#include <iostream>
#include <vector>
#include <array>

MainWindow::MainWindow()
{
    createGLWindow();

    checkWindowLoaded();
    glfwMakeContextCurrent(window);
    checkGladLoaded();

    glViewport(0,0,800,600);
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.0f,.0f,.0f,1.0f);  

    shader.createShaderProgram();

    //intializing the transformation matrices in the shader
    model = glm::mat4(1.0f);    
    view = glm::mat4(1.0f);    
    projection = glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f, -1.0f, 1.0f); 
    
    orbitalView.initializeGLBuffers();

    glfwSetKeyCallback(window, keyCallback);
    glfwSetWindowUserPointer(window, this);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    sim.addSatellite(6.8e6,0,0,0);  //temp
}

void MainWindow::createGLWindow()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);
    window = glfwCreateWindow(1000,1000,"Satellite Network Sim",NULL,NULL);
}

void MainWindow::checkWindowLoaded()
{
    if(window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        throw std::runtime_error("Failed to create GLFW window");
    }
}

void MainWindow::checkGladLoaded()
{
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize Glad" << std::endl;
        throw std::runtime_error("Failed to initialize GLAD");
    }
}

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
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
            UI->setSimSpeed(1);
            break;
        case GLFW_KEY_2:
            UI->setSimSpeed(10);
            break;
        case GLFW_KEY_3:
            UI->setSimSpeed(100);
            break;
        case GLFW_KEY_4:
            UI->setSimSpeed(1000);
            break;
        case GLFW_KEY_5:
            UI->setSimSpeed(10000);
            break;
        }
    }
}

void MainWindow::setSimSpeed(float newSpeed)
{
    sim.setTimeStep(newSpeed);
    std::cout << "Time Step Changed to " << newSpeed << "s" << std::endl;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0,0,width,height);
}

void MainWindow::run()
{
    while(!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        sim.runTimeStep();

        //eventually for zoom in/out
        //projection = glm::ortho(-2.0f, 2.0f, -2.0f, 2.0f, -2.0f, 2.0f);

        glUniformMatrix4fv(shader.modelLoc, 1, GL_FALSE, glm::value_ptr(model));    
        glUniformMatrix4fv(shader.viewLoc, 1, GL_FALSE, glm::value_ptr(view));    
        glUniformMatrix4fv(shader.projLoc, 1, GL_FALSE, glm::value_ptr(projection));
        glUseProgram(shader.shaderProgram);

        std::vector<std::array<double,3>> satPos = sim.getSatellitePositions();
        orbitalView.render(satPos);

        glfwSwapBuffers(window);

        glfwPollEvents();
    }
}

MainWindow::~MainWindow()   
{ 
    glfwTerminate();    
}