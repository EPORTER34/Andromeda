#include "MainWindow.hpp"

MainWindow::MainWindow()
{
    //Open GL window setup
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);
    window = glfwCreateWindow(800,600,"Satellite Network Sim",NULL,NULL);

    //checks
    if(window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return ; //replace with exception
    }
    glfwMakeContextCurrent(window);

    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return ; //replace with exception
    }

    glViewport(0,0,800,600); //sets the viewing range for rendering
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
}

MainWindow::~MainWindow()   { glfwTerminate(); }


void MainWindow::run()
{
    while(!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //clear screen

        //render here

        glfwSwapBuffers(window); //swap rendering buffers
        glfwPollEvents(); //check for resize
    }
}

//resizing the window
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0,0,width,height);
}