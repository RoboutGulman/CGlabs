#include "stdafx.h"

#include "GLFWInitializer.h"
#include "include/Window.h"
// � ����� ������� ��������� ��� ������� (������ 19 ������ � ���������)
int main(void)
{
	GLFWInitializer glfwInitializer;
	Window window{ 1200, 900, "Cottage" };
	window.Run();
}
