#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <cmath>

void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void processInput(GLFWwindow *window);
unsigned int compileShader(unsigned int type, const char *source);
unsigned int createShaderProgram(const char *vertexSrc, const char *fragmentSrc);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

int main()
{
	// glfw: initialize and configure
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	GLFWwindow *window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "3D Cube", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	glClearColor(0.1f, 0.1f, 0.15f, 1.0f);
	glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);
	glEnable(GL_DEPTH_TEST);  // Enable depth testing for 3D

	// Vertex Shader
	const char *vertexShaderSource = R"(
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
	const char *fragmentShaderSource = R"(
		#version 330 core
		in vec3 vertexColor;
		out vec4 FragColor;

		void main()
		{
			FragColor = vec4(vertexColor, 1.0);
		}
	)";

	unsigned int shaderProgram = createShaderProgram(vertexShaderSource, fragmentShaderSource);

	// Cube vertices (position + color)
	float vertices[] = {
		// Front face (red)
		-0.5f, -0.5f,  0.5f,   1.0f, 0.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,   1.0f, 0.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,   1.0f, 0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,   1.0f, 0.0f, 0.0f,

		// Back face (green)
		-0.5f, -0.5f, -0.5f,   0.0f, 1.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,   0.0f, 1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,   0.0f, 1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,   0.0f, 1.0f, 0.0f,

		// Left face (blue)
		-0.5f, -0.5f, -0.5f,   0.0f, 0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,   0.0f, 0.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,   0.0f, 0.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,   0.0f, 0.0f, 1.0f,

		// Right face (yellow)
		 0.5f, -0.5f, -0.5f,   1.0f, 1.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,   1.0f, 1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,   1.0f, 1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,   1.0f, 1.0f, 0.0f,

		// Top face (cyan)
		-0.5f,  0.5f,  0.5f,   0.0f, 1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,   0.0f, 1.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,   0.0f, 1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,   0.0f, 1.0f, 1.0f,

		// Bottom face (magenta)
		-0.5f, -0.5f,  0.5f,   1.0f, 0.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,   1.0f, 0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,   1.0f, 0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,   1.0f, 0.0f, 1.0f,
	};

	// Cube indices (which vertices to connect)
	unsigned int indices[] = {
		0, 1, 2, 2, 3, 0,       // Front
		4, 6, 5, 6, 4, 7,       // Back
		8, 10, 9, 10, 8, 11,    // Left
		12, 13, 14, 14, 15, 12, // Right
		16, 17, 18, 18, 19, 16, // Top
		20, 21, 22, 22, 23, 20  // Bottom
	};

	unsigned int VAO, VBO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// Color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	std::cout << "3D Cube loaded. Close with ESC." << std::endl;

	// Render loop
	while (!glfwWindowShouldClose(window))
	{
		processInput(window);

		// Clear color and depth buffers
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glUseProgram(shaderProgram);

		// Create model matrix (rotation)
		glm::mat4 model = glm::mat4(1.0f);
		float time = (float)glfwGetTime();
		model = glm::rotate(model, time * glm::radians(50.0f), glm::vec3(1.0f, 1.0f, 0.5f));

		// Create view matrix (camera position)
		glm::mat4 view = glm::mat4(1.0f);
		view = glm::translate(view, glm::vec3(0.0f, 0.0f, -2.0f));

		// Create projection matrix (perspective)
		glm::mat4 projection = glm::perspective(
			glm::radians(45.0f),
			(float)SCR_WIDTH / (float)SCR_HEIGHT,
			0.1f,
			100.0f
		);

		// Pass matrices to shader
		unsigned int modelLoc = glGetUniformLocation(shaderProgram, "model");
		unsigned int viewLoc = glGetUniformLocation(shaderProgram, "view");
		unsigned int projLoc = glGetUniformLocation(shaderProgram, "projection");

		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

		// Draw cube
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// Cleanup
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	glDeleteVertexArrays(1, &VAO);
	glDeleteProgram(shaderProgram);

	glfwTerminate();
	return 0;
}

void processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
	glViewport(0, 0, width, height);
}

unsigned int compileShader(unsigned int type, const char *source)
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
	}

	return id;
}

unsigned int createShaderProgram(const char *vertexSrc, const char *fragmentSrc)
{
	unsigned int vertexShader = compileShader(GL_VERTEX_SHADER, vertexSrc);
	unsigned int fragmentShader = compileShader(GL_FRAGMENT_SHADER, fragmentSrc);

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
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	return program;
}
