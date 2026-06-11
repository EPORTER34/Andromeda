#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "string"

class Shader
{
public:
    void createShaderProgram();
    ~Shader();

    unsigned int shaderProgram;
    GLint modelLoc;    
    GLint viewLoc;    
    GLint projLoc; 

private:
    unsigned int getShader(GLenum shaderType, std::string filePath);
    std::string readFile(std::string filePath);
    unsigned int compileShader(unsigned int type, const char *source);

    
};