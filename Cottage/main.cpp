#include "stdafx.h"

#include "GLFWInitializer.h"
#include "include/Window.h"
// в какой системе координат это задаётся (шейдер 19 строка с нормалями)
int main(void)
{
	GLFWInitializer glfwInitializer;
	Window window{ 1200, 900, "Cottage" };
	window.Run();
}
