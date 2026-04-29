#pragma once
#include <vector>
#include<initializer_list>

class Spheroid
{
public:
    Spheroid(float majorAxis, float minorAxis, std::initializer_list<float> color);
    void initialize();
    ~Spheroid();
    void render();
    unsigned int getVAO() const;
private:
    void pushVertex(std::initializer_list<float> vertex, std::initializer_list<float> color);
    
    std::vector<float> vertices;
    std::vector<unsigned int> indexBuffer;
    unsigned int VAO;
    unsigned int VBO;
    unsigned int EBO;
};