#pragma once
#include <initializer_list>
#include <vector>

class Cube
{
public:
    Cube(float length, std::initializer_list<float> color);
private:
    void generateVertices(float length, std::initializer_list<float> color);
    void generateSquare(float length, float depth, std::initializer_list<float> color);
    void pushVertex(std::initializer_list<float> point, std::initializer_list<float> color);
    void generateIndexBuffer();

    std::vector<float> vertices;
    std::vector<unsigned int> indexBuffer;
    unsigned int VAO;
    unsigned int VBO;
    unsigned int EBO;
};