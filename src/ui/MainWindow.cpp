#include "MainWindow.hpp"
#include "../util/constants.hpp"

#include <iostream>
#include <vector>
#include <array>
#include <fstream>
#include <sstream>

MainWindow::MainWindow()
{
    createGLWindow();

    checkWindowLoaded();
    glfwMakeContextCurrent(window);
    checkGladLoaded();
    setWindowAttributes();

    shader.createShaderProgram();

    initTransformationMatrices();
    
    orbitalView.initializeGLBuffers();
    orbitalView.setShaderProgram(shader);

    //TODO: add a menu for these & others
    //loadNetworkFromCSV("resource/networks/GPS.csv");
    loadNetworkFromCSV("resource/networks/Kuiper_Network.csv");
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

void MainWindow::setWindowAttributes()
{
    glViewport(0,0,800,600);
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.0f,.0f,.0f,1.0f);  
    glfwSetKeyCallback(window, keyCallback);
    glfwSetWindowUserPointer(window, this);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetScrollCallback(window, scrollCallback);

    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

void MainWindow::initTransformationMatrices()
{
    model = glm::mat4(1.0f);    
    view = glm::mat4(1.0f);    
    projection = glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f, -1.0f, 1.0f); 
}

void MainWindow::loadNetworkFromCSV(std::string filePath)
{
    std::ifstream input(filePath);
    std::string line;
    const double degToRad = PI / 180;

    if (!std::getline(input, line))     return ;

    while (std::getline(input, line))
    {
        if (line.empty())
            continue;

        std::stringstream ss(line);
        std::string field;

        std::getline(ss, field, ',');
        std::string name = field;

        std::getline(ss, field, ',');
        double radius = 1e3 * std::stod(field);

        std::getline(ss, field, ',');
        double inclination = degToRad * std::stod(field);

        std::getline(ss, field, ',');
        double raan = degToRad * std::stod(field);

        std::getline(ss, field, ',');
        double initialAnomaly = degToRad * std::stod(field);

        sim.addSatellite(name, radius, inclination, raan, initialAnomaly);
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

void MainWindow::setSimSpeed(float newSpeed)
{
    sim.setTimeStep(newSpeed);
    std::cout << "Time Step Changed to " << newSpeed << "s" << std::endl;
}

void scrollCallback(GLFWwindow* window, double horzScroll, double vertScroll)
{
    MainWindow* UI = static_cast<MainWindow*>(glfwGetWindowUserPointer(window));
    if(vertScroll > 0) UI->zoomOrbitalIn();
    else UI->zoomOrbitalOut();
}

void MainWindow::zoomOrbitalIn()
{
    orbitalView.zoomIn();
    std::cout << "Orbital View Zoomed In" << std::endl;
}

void MainWindow::zoomOrbitalOut()
{
    orbitalView.zoomOut();
    std::cout << "Orbital View Zoomed Out" << std::endl; 
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

        glUseProgram(shader.getShaderProgram());
        glUniformMatrix4fv(shader.getModelLoc(), 1, GL_FALSE, glm::value_ptr(model));    
        glUniformMatrix4fv(shader.getViewLoc(), 1, GL_FALSE, glm::value_ptr(view));    
        glUniformMatrix4fv(shader.getProjLoc(), 1, GL_FALSE, glm::value_ptr(projection));

        std::vector<std::array<double,3>> satPos = sim.getSatellitePositionsECI();
        orbitalView.render(satPos);

        glfwSwapBuffers(window);

        glfwPollEvents();
    }
}

MainWindow::~MainWindow()   
{ 
    glfwTerminate();    
}