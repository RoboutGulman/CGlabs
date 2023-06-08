#include "stdafx.h"

#include "GLFWInitializer.h"
#include "include/Window.h"

#include <iostream>
#include "include/utils.h"

int main(void)
{
	//std::cout << BernoulliFormula(3, 0, 4.0 / 9) << std::endl;
	GLFWInitializer glfwInitializer;
	Window window{ 800, 600, "Weapon effectiveness" };
	window.Run();
}
