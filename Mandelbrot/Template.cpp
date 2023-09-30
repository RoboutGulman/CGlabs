#include "stdafx.h"

#include "GLFWInitializer.h"
#include "include/Window.h"

int main(void)
{
	GLFWInitializer glfwInitializer;
	Window window{ 800, 600, "Hello World" };
	window.Run();
}
