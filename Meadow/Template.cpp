#include "stdafx.h"

#include "GLFWInitializer.h"
#include "include/Window.h"

int main(void)
{
	GLFWInitializer glfwInitializer;
	Window window{ 1000, 800, "Meadow" };
	window.Run();
}
