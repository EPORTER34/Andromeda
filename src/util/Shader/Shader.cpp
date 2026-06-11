#include "Shader.hpp"

#include <iostream>
#include <fstream>
#include <sstream>

void Shader::createShaderProgram()
{
    unsigned int vertexShader = getShader(GL_VERTEX_SHADER, "resource/shaders/basic.vert");
    unsigned int fragmentShader = getShader(GL_FRAGMENT_SHADER, "resource/shaders/basic.frag");

	unsigned int program = glCreateProgram();
	glAttachShader(program, vertexShader);
	glAttachShader(program, fragmentShader);
	glLinkProgram(program);

	int success;
	glGetProgramiv(program, GL_LINK_STATUS, &success);
	if (!success)
	{
        char infoLog[512];
		glGetProgramInfoLog(program, 512, NULL, infoLog);
		std::cout << "ERROR::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
        throw std::runtime_error("Error Linking Program");
	}

    shaderProgram = program;

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

    modelLoc = glGetUniformLocation(shaderProgram, "model");    
    viewLoc = glGetUniformLocation(shaderProgram, "view");    
    projLoc = glGetUniformLocation(shaderProgram, "projection"); 
}

unsigned int Shader::getShader(GLenum shaderType, std::string filePath)
{
    std::string shaderSource = readFile(filePath);
    const char* cShaderSource = shaderSource.c_str();
    return compileShader(shaderType, cShaderSource);
}

std::string Shader::readFile(std::string filePath)
{
    std::ifstream file(filePath);

    if (!file)
    {
        throw std::runtime_error("Failed to open file: " + filePath);
    }
    std::stringstream buffer;
    buffer << file.rdbuf();

    return buffer.str();
}

unsigned int Shader::compileShader(unsigned int type, const char *source)
{
	unsigned int id = glCreateShader(type);
	glShaderSource(id, 1, &source, NULL);
	glCompileShader(id);

	int success;
	glGetShaderiv(id, GL_COMPILE_STATUS, &success);
	if (!success)
	{   
        char infoLog[512];
		glGetShaderInfoLog(id, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
        throw std::runtime_error("Error compiling shaders");
	}

	return id;
}

Shader::~Shader()
{
    glDeleteProgram(shaderProgram);
}