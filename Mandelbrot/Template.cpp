#include "stdafx.h"

#include "GLFWInitializer.h"
#include "include/Window.h"
//������ ���������� ��������� ������� � ���������� �������, ���������� varying ����������
int main(void)
{
	GLFWInitializer glfwInitializer;
	Window window{ 800, 600, "Mandelbrot" };
	window.Run();
}
