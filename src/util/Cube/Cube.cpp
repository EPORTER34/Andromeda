#include "Cube.hpp"

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
    for(int i = 0; i < 8; ++i)
    {
        indexBuffer.push_back(i);
        indexBuffer.push_back((i + 1) % 8);
        indexBuffer.push_back((i + 2) % 8);
    }
    //TODO: add the top & bottom faces
}