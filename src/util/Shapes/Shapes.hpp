#pragma once
#include <vector>
#include<initializer_list>


class Shape
{
public:
    ~Shape();
    void initializeGLBuffers();
    void render();

protected:
    void pushVertex(std::initializer_list<float> point, std::initializer_list<float> color);

    std::vector<float> vertices;
    std::vector<unsigned int> indexBuffer;
    unsigned int VAO;
    unsigned int VBO;
    unsigned int EBO;
};

class Spheroid : public Shape
{
public:
    Spheroid(float majorAxis, float minorAxis, std::initializer_list<float> color);
protected:
    std::vector<int> generateVertices(float majorAxis, float minorAxis, std::initializer_list<float> color);
    void generateRing(float majorAxis, float minorAxis, float v, std::initializer_list<float> color);
    void generateIndexBuffer(std::vector<int> ringStarts);
};

class Sphere : public Spheroid
{
public:
    Sphere(float radius, std::initializer_list<float> color) : Spheroid(radius, radius, color) {}
};

class Cube : public Shape
{
public:
    Cube(float length, std::initializer_list<float> color);
private:
    void generateVertices(float length, std::initializer_list<float> color);
    void generateSquare(float length, float depth, std::initializer_list<float> color);
    void generateIndexBuffer();
};