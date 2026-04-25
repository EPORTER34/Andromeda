#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <cmath>

#include "ui/MainWindow.hpp"
#include "ui/MainWindow.cpp"

int main()
{
	MainWindow app;
	app.run();
	return 0;
}