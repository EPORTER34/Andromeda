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
    unsigned int getVAO() const;

private:
    std::vector<int> initializeVertices(float majorAxis, float minorAxis, std::initializer_list<float> color);
    void pushVertex(std::initializer_list<float> vertex, std::initializer_list<float> color);
    void initializeIndexBuffer(std::vector<int> ringStarts);
    
    std::vector<float> vertices;
    std::vector<unsigned int> indexBuffer;
    unsigned int VAO;
    unsigned int VBO;
    unsigned int EBO;
};