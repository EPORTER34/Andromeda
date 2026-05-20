#include "MainWindow.hpp"

void setSimTime(MainWindow* UI, float newTime)
{
    UI->sim.setTimeStep(newTime);
    std::cout << "Time Step Changed to " << newTime << "s" << std::endl;
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
            setSimTime(UI, 1);
            break;
        case GLFW_KEY_2:
            setSimTime(UI, 10);
            break;
        case GLFW_KEY_3:
            setSimTime(UI, 100);
            break;
        case GLFW_KEY_4:
            setSimTime(UI, 1000);
            break;
        case GLFW_KEY_5:
            setSimTime(UI, 10000);
            break;
        }
    }
}

//earth radii:: equator: 6378km  poles: 6357km
MainWindow::MainWindow() : earth(6378, 6357, {.0f,.0f,1.0f })
{
    //Open GL window setup
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);
    window = glfwCreateWindow(1000,1000,"Satellite Network Sim",NULL,NULL);

    //checks
    if(window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        throw std::runtime_error("Failed to create GLFW window");
    }
    glfwMakeContextCurrent(window);

    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        throw std::runtime_error("Failed to initialize GLAD");
    }

    glViewport(0,0,800,600); //sets the screen-space transform (scalar) for normalized device coordinates
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback); //gives a function for if the window is resized
    glEnable(GL_DEPTH_TEST); //enables graphics card to use depth values to determine which objects are in front of others

    // Vertex Shader
	vertexShaderSource = R"(
		#version 330 core

		layout (location = 0) in vec3 aPos;
		layout (location = 1) in vec3 aColor;
		out vec3 vertexColor;

		uniform mat4 model;
		uniform mat4 view;
		uniform mat4 projection;
		void main()
		{
			gl_Position = projection * view * model * vec4(aPos, 1.0);
			vertexColor = aColor;
		}
	)";

	// Fragment Shader
	fragmentShaderSource = R"(
		#version 330 core
		in vec3 vertexColor;
		out vec4 FragColor;
		void main()
		{
			FragColor = vec4(vertexColor, 1.0);
		}
	)";
    shaderProgram = createShaderProgram(); //compile shaders

    //intializing the transformation matrices in the shader
    model = glm::mat4(1.0f);    
    view = glm::mat4(1.0f);    
    projection = glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f, -1.0f, 1.0f);        
    modelLoc = glGetUniformLocation(shaderProgram, "model");    
    viewLoc = glGetUniformLocation(shaderProgram, "view");    
    projLoc = glGetUniformLocation(shaderProgram, "projection"); 

    glClearColor(0.0f,.0f,.0f,1.0f);  
    
    earth.initializeGlBuffers();

    glfwSetKeyCallback(window, keyCallback);
    glfwSetWindowUserPointer(window, this);
}

MainWindow::~MainWindow()   
{ 
    glDeleteProgram(shaderProgram);
    glfwTerminate();    
}

void MainWindow::run()
{
    while(!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //clear screen

        sim.runTimeStep();

        //eventually for zoom in/out
        //projection = glm::ortho(-2.0f, 2.0f, -2.0f, 2.0f, -2.0f, 2.0f);

        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));    
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));    
        glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
        glUseProgram(shaderProgram);

        earth.render();

        glfwSwapBuffers(window); //swap rendering buffers
        glfwPollEvents(); //check for resize
    }
}

//resizing the window
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0,0,width,height);
}

unsigned int MainWindow::compileShader(unsigned int type, const char *source)
{
	unsigned int id = glCreateShader(type);
	glShaderSource(id, 1, &source, NULL);
	glCompileShader(id);

	int success;
	char infoLog[512];
	glGetShaderiv(id, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(id, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
        throw std::runtime_error("Error compiling shaders");
	}

	return id;
}

unsigned int MainWindow::createShaderProgram()
{
	unsigned int vertexShader = compileShader(GL_VERTEX_SHADER, vertexShaderSource);
	unsigned int fragmentShader = compileShader(GL_FRAGMENT_SHADER, fragmentShaderSource);

	unsigned int program = glCreateProgram();
	glAttachShader(program, vertexShader);
	glAttachShader(program, fragmentShader);
	glLinkProgram(program);

	int success;
	char infoLog[512];
	glGetProgramiv(program, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(program, 512, NULL, infoLog);
		std::cout << "ERROR::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
        throw std::runtime_error("Error Linking Program");
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	return program;
}