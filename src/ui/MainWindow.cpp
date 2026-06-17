#include "MainWindow.hpp"
#include "../util/constants.hpp"
#include "../util/Input/Input.hpp"

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
    Input::setCallbackFunctions(window);

    shader.createShaderProgram();

    initTransformationMatrices();
    
    orbitalView.initializeGLBuffers();
    orbitalView.setShaderProgram(shader);

    //TODO: add a menu for these & others
    loadNetworkFromCSV("resource/networks/GPS.csv");
    loadNetworkFromCSV("resource/networks/Kuiper_Network.csv");
    loadNetworkFromCSV("resource/networks/Starlink_Network.csv");
}

void MainWindow::createGLWindow()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);
    window = glfwCreateWindow(1920,1080,"Satellite Network Sim",NULL,NULL);
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
    glfwSetWindowUserPointer(window, this);
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

        OrbitalElements newOrbit;

        std::getline(ss, field, ',');
        newOrbit.radius = 1e3 * std::stod(field);

        std::getline(ss, field, ',');
        newOrbit.inclination = degToRad * std::stod(field);

        std::getline(ss, field, ',');
        newOrbit.RAAN = degToRad * std::stod(field);

        std::getline(ss, field, ',');
        newOrbit.initialAnomaly = degToRad * std::stod(field);

        sim.addSatellite(name, newOrbit);
    }
}

void MainWindow::setSimSpeed(float newSpeed)
{
    sim.setTimeStep(newSpeed);
    std::cout << "Time Step Changed to " << newSpeed << "s" << std::endl;
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

void MainWindow::rotateOrbital(double deltaX, double deltaY)
{
    orbitalView.rotateLeftRight(deltaX);
    orbitalView.rotateUpDown(deltaY);
}

 void MainWindow::resizeWindow(int width, int height)
 {
    orbitalView.resizeWindow(width, height);
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