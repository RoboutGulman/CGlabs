#include "stdafx.h"

#include "GLFWInitializer.h"
#include "include/Window.h"
//shader ��������� �������� �� 90
//�����: �������� ����� � ������� �������
int main(void)
{
	GLFWInitializer glfwInitializer;
	Window window{ 800, 600, "Hello World" };
	window.Run();
}
