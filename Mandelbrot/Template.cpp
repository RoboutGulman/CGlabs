#include "stdafx.h"

#include "GLFWInitializer.h"
#include "include/Window.h"
//вместо вычисления координат пикселя в фрагментом шейдере, передавать varying переменные
int main(void)
{
	GLFWInitializer glfwInitializer;
	Window window{ 800, 600, "Mandelbrot" };
	window.Run();
}
