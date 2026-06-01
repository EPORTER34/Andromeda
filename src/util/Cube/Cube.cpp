#include "Cube.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Cube::Cube(float length, std::initializer_list<float> color)
{
    generateVertices(length, color);
    generateIndexBuffer();
}

void Cube::generateVertices(float length, std::initializer_list<float> color)
{
    generateSquare(length, 0, color);
    generateSquare(length, length, color);
}

void Cube::generateSquare(float length, float depth, std::initializer_list<float> color)
{
    pushVertex({0,0,depth},color);
    pushVertex({0,length,depth},color);
    pushVertex({length,0,depth},color);
    pushVertex({length,length,depth},color);
}

void Cube::pushVertex(std::initializer_list<float> point, std::initializer_list<float> color)
{
    for(float x : point) vertices.push_back(x);
    for(float x : color) vertices.push_back(x);
}

void Cube::generateIndexBuffer()
{
    for(int i = 1; i < 9; ++i)
    {
        indexBuffer.push_back(i);
        indexBuffer.push_back((i + 1) % 8);
        indexBuffer.push_back((i + 2) % 8);
    }
    indexBuffer.push_back(1);
    indexBuffer.push_back(5);
    indexBuffer.push_back(6);

    indexBuffer.push_back(1);
    indexBuffer.push_back(2);
    indexBuffer.push_back(6);

    indexBuffer.push_back(3);
    indexBuffer.push_back(7);
    indexBuffer.push_back(8);

    indexBuffer.push_back(3);
    indexBuffer.push_back(4);
    indexBuffer.push_back(8);
}

void Cube::initializeGlBuffers()
{
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(GL_ARRAY_BUFFER, vertices.size()*sizeof(float), vertices.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0,3, GL_FLOAT, GL_FALSE, 6*sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6*sizeof(float), (void*)(3*sizeof(float)));    
    glEnableVertexAttribArray(1);

    glGenBuffers(1, &EBO);  
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexBuffer.size() * sizeof(unsigned int), indexBuffer.data(), GL_STATIC_DRAW);
}

Cube::~Cube()
{
    glDeleteBuffers(1, &VBO);
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &EBO);
}

void Cube::render()
{
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, indexBuffer.size(), GL_UNSIGNED_INT, 0);
}