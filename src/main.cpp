#include <iostream>
#include <cmath>

#include "ui/MainWindow.hpp"
#include "ui/MainWindow.cpp"

int main()
{
	MainWindow app;
	app.run(); //rework so it doesn't run if the window didn't load properly
	return 0;
}