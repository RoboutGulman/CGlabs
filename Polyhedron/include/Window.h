#pragma once
#include "stdafx.h"

#include "BaseWindow.h"
#include "Renderer.h"

#include "Controls.h"
#include "SnubDodecahedron.h"

class Window : public BaseWindow
{
public:
	Window(int w, int h, const char* title)
		: BaseWindow(w, h, title)
		, m_controls()
		, m_shader("res/shaders/Basic.shader")
		, m_renderer()
		, m_polyhedron()

	{
		glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	}

private:
	Renderer m_renderer;
	Shader m_shader;
	SnubDodecahedron m_polyhedron;

	Controls m_controls;

	void Draw(int width, int height, ImGuiIO& io) override
	{
		m_renderer.Clear();

		m_shader.Bind();
		m_shader.SetUniformMatrix4fv("MVP", m_controls.GetMVPMatrix(m_window, width, height));

		m_polyhedron.Draw(m_renderer, m_shader);
	}
};
