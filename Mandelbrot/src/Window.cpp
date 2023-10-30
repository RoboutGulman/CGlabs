#include "stdafx.h"

#include "../include/Window.h"

int ZOOM = 0;
double LAST_X = 0;
double LAST_Y = 0;
bool IS_FIRST_CLICK = true;
bool IS_MOUSE_BUTTON_LEFT_DOWN = false;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void mouseButtonCallback(GLFWwindow* _window, int button, int action, int mods);

Window::Window(int w, int h, const char* title)
	: BaseWindow(w, h, title)
	, m_shader("res/shaders/Basic.shader")
	, m_renderer()
	, m_mandelbrot(glm::vec3{ 0, 0, 0 }, w, h, "res\\assets\\pallete.png", glm::vec4{ 1.0f })
	, m_controls(0.0f, 0.0f, 0.0025f)
{
	m_shader.Bind();
	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 projection = glm::ortho(0.0f, float(w), float(h), 0.0f, -1.0f, 100.0f);
	m_shader.SetUniformMatrix4fv("u_view", view);
	m_shader.SetUniformMatrix4fv("u_projection", projection);
	m_shader.SetUniform2f("resolution", w, h);

	glfwSetKeyCallback(m_window, key_callback);
	glfwSetMouseButtonCallback(m_window, mouseButtonCallback);
}

void Window::Draw(int width, int height, ImGuiIO& io)
{
	m_renderer.Clear();

	if (IS_MOUSE_BUTTON_LEFT_DOWN)
	{
		Move();
	}
	if (0 < ZOOM)
	{
		ZoomWindow();
	}
	else if (ZOOM < 0)
	{
		UnzoomWindow();
	}

	m_shader.Bind();
	m_shader.SetUniform1f("zoom", m_controls.GetZoomNormalized());
	m_shader.SetUniform2f("mouseDelta", m_controls.GetX(), m_controls.GetY());
	m_mandelbrot.Draw(m_renderer, m_shader);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
		return;
	}

	if (key == GLFW_KEY_PAGE_UP && action == GLFW_PRESS)
	{
		ZOOM = 1;
	}

	if (key == GLFW_KEY_PAGE_DOWN && action == GLFW_PRESS)
	{
		ZOOM = -1;
	}
}

void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
	switch (button)
	{
	case GLFW_MOUSE_BUTTON_LEFT:
		if (action == GLFW_PRESS)
		{
			IS_MOUSE_BUTTON_LEFT_DOWN = true;
		}
		else if (action == GLFW_RELEASE)
		{
			IS_MOUSE_BUTTON_LEFT_DOWN = false;
			IS_FIRST_CLICK = true;
		}
	}
}

void Window::Move()
{
	double xpos;
	double ypos;
	glfwGetCursorPos(m_window, &xpos, &ypos);

	if (IS_FIRST_CLICK)
	{
		IS_FIRST_CLICK = false;
		LAST_X = xpos;
		LAST_Y = ypos;
	}

	double deltaX = xpos - LAST_X;
	double deltaY = ypos - LAST_Y;

	LAST_X = xpos;
	LAST_Y = ypos;

	m_controls.Move(static_cast<float>(deltaX), static_cast<float>(deltaY));
}

void Window::ZoomWindow()
{
	m_controls.Zoom();
	ZOOM = 0;
}

void Window::UnzoomWindow()
{
	m_controls.Unzoom();
	ZOOM = 0;
}
