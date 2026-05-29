#pragma once
#include <vector>
#include<initializer_list>

class Spheroid
{
public:
    Spheroid(float majorAxis, float minorAxis, std::initializer_list<float> color);
    void initializeGlBuffers();
    ~Spheroid();
    void render();

private:
    std::vector<int> generateVertices(float majorAxis, float minorAxis, std::initializer_list<float> color);
    void pushVertex(std::initializer_list<float> vertex, std::initializer_list<float> color);
    void generateRing(float glMajor, float glMinor, float v, std::initializer_list<float> color);
    void generateIndexBuffer(std::vector<int> ringStarts);
    
    std::vector<float> vertices;
    std::vector<unsigned int> indexBuffer;
    unsigned int VAO;
    unsigned int VBO;
    unsigned int EBO;
};