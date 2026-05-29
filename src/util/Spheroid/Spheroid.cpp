#include "Spheroid.hpp"
#include "../constants.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <cmath>

Spheroid::Spheroid(float majorAxis, float minorAxis, std::initializer_list<float> color)
{
    std::vector<int> ringStarts = generateVertices(majorAxis, minorAxis, color);
    generateIndexBuffer(ringStarts);
}

//vertices in format (x,y,z) + (r,g,b)
std::vector<int> Spheroid::generateVertices(float majorAxis, float minorAxis, std::initializer_list<float> color)
{
    float glMajor = .5;
    float glMinor = glMajor * minorAxis / majorAxis;

    std::vector<int> ringStarts;

    //front point
    ringStarts.push_back(0);
    pushVertex({glMajor,0,0}, color);

    for(float v = PI/24; v < PI; v += PI/24)
    {
        ringStarts.push_back(vertices.size() / 6);
        generateRing(glMajor, glMinor, v, color);
    }

    //back point
    ringStarts.push_back(vertices.size() / 6);
    pushVertex({-glMajor,0,0}, color);

    return ringStarts;
}

void Spheroid::pushVertex(std::initializer_list<float> vertex, std::initializer_list<float> color)
{
    for(float x : vertex) vertices.push_back(x);
    for(float x : color) vertices.push_back(x);
}

void Spheroid::generateRing(float glMajor, float glMinor, float v, std::initializer_list<float> color)
{
    float r = glMinor*sin(v);
    for(float theta = 0; theta < 2*PI; theta += PI/12)
    {  
        pushVertex({glMajor*(float)cos(v), r*(float)cos(theta), r*(float)sin(theta)}, 
                   {color.begin()[0], 1 - theta/(2*(float)PI), color.begin()[2]});
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

void Spheroid::initializeGlBuffers()
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

Spheroid::~Spheroid()
{
    glDeleteBuffers(1, &VBO);
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &EBO);
}

void Spheroid::render()
{
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, indexBuffer.size(), GL_UNSIGNED_INT, 0);
}