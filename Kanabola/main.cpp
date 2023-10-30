#include "stdafx.h"

#include "GLFWInitializer.h"
#include "include/Window.h"
//shader повернуть канаболу на 90
//ответ: поменять синус и косинус местами
int main(void)
{
	GLFWInitializer glfwInitializer;
	Window window{ 800, 600, "Hello World" };
	window.Run();
}
