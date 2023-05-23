#include "stdafx.h"

#include "GLFWInitializer.h"
#include "include/View/Window.h"

#include <vector>

int main(void)
{
	std::vector<glm::vec2> startPoints{
		{ 200.0f, 600.0f },
		{ 430.0f, 150.0f },
		{ 750.0f, 300.0f },
		{ 600.0f, 400.0f }
	};
	GLFWInitializer glfwInitializer;
	Window window{1000,	800,"Bezier Curve", 
		startPoints[0], startPoints[1], startPoints[2], startPoints[3]
	};
	window.Run();
}
