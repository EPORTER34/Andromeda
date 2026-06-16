#include "Shapes.hpp"
#include "../constants.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <cmath>

Shape::~Shape()
{
    glDeleteBuffers(1, &VBO);
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &EBO);
}

void Shape::initializeGLBuffers()
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

void Shape::render()
{
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, indexBuffer.size(), GL_UNSIGNED_INT, 0);
}

void Shape::pushVertex(std::initializer_list<float> point, std::initializer_list<float> color)
{
    for(float x : point) vertices.push_back(x);
    for(float x : color) vertices.push_back(x);
}


Spheroid::Spheroid(float majorAxis, float minorAxis, std::initializer_list<float> color)
{
    std::vector<int> ringStarts = generateVertices(majorAxis, minorAxis, color);
    generateIndexBuffer(ringStarts);
}

//vertices in format (x,y,z) + (r,g,b)
std::vector<int> Spheroid::generateVertices(float majorAxis, float minorAxis, std::initializer_list<float> color)
{
    std::vector<int> ringStarts;

    //front point
    ringStarts.push_back(0);
    pushVertex({majorAxis,0,0}, color);

    for(float v = PI/24; v < PI; v += PI/24)
    {
        ringStarts.push_back(vertices.size() / 6);
        generateRing(majorAxis, minorAxis, v, color);
    }

    //back point
    ringStarts.push_back(vertices.size() / 6);
    pushVertex({-majorAxis,0,0}, color);

    return ringStarts;
}

void Spheroid::generateRing(float majorAxis, float minorAxis, float v, std::initializer_list<float> color)
{
    float r = minorAxis*sin(v);
    for(float theta = 0; theta < 2*PI; theta += PI/12)
    {  
        pushVertex({majorAxis*(float)cos(v), r*(float)cos(theta), r*(float)sin(theta)}, color);
    }
}

void Spheroid::generateIndexBuffer(std::vector<int> ringStarts)
{
    int ringSize = ringStarts[2] - ringStarts[1];

    //front
    for(int i = 0; i < ringSize; ++i)
    {
        indexBuffer.push_back(0);
        indexBuffer.push_back(1 + i);
        indexBuffer.push_back(1 + (i + 1) % ringSize);
    }

    //middle
    for(int i = 0; i < ringStarts.size() - 1; ++i)
    {
        for(int j = 0; j < ringSize; ++j)
        {
            int next = (j + 1) % ringSize;
            indexBuffer.push_back(ringStarts[i] + j);
            indexBuffer.push_back(ringStarts[i+1] + j);
            indexBuffer.push_back(ringStarts[i] + next);
            indexBuffer.push_back(ringStarts[i] + next);
            indexBuffer.push_back(ringStarts[i+1] + j);
            indexBuffer.push_back(ringStarts[i+1] + next);
        }
    }

    //back
    int size = vertices.size()/6 - 1;
    for(int i = 0; i < ringSize; ++i)
    {
        indexBuffer.push_back(size);
        indexBuffer.push_back(size - 1 - i);
        indexBuffer.push_back(size - 1 - (i + 1) % ringSize);
    }
}


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

void Cube::generateIndexBuffer()
{
    indexBuffer = {
    // Front
    0,1,2,
    2,1,3,

    // Back
    4,6,5,
    6,7,5,

    // Left
    0,4,1,
    1,4,5,

    // Right
    2,3,6,
    3,7,6,

    // Bottom
    0,2,4,
    2,6,4,

    // Top
    1,5,3,
    3,5,7
    };
}