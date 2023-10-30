#pragma once
#include "stdafx.h"

#include "BaseWindow.h"
#include "Line.h"
#include "Renderer.h"
#include <Primitives/Rectangle.h>

class Window : public BaseWindow
{
public:
	Window(int w, int h, const char* title)
		: BaseWindow(w, h, title)
		, m_shader("res/shaders/Basic.shader")
		, m_renderer()
		, m_line(0, 2 * 3.14f, 3000, 300, 300, glm::vec3{ 400, 400, 0 })
	{
		m_shader.Bind();
		glm::mat4 view = glm::mat4(1.0f);
		glm::mat4 projection = glm::ortho(0.0f, float(w), float(h), 0.0f, -1.0f, 100.0f);
		m_shader.SetUniformMatrix4fv("u_view", view);
		m_shader.SetUniformMatrix4fv("u_projection", projection);
		m_shader.SetUniformMatrix4fv("u_model", glm::mat4(1.0f));
	}

private:
	Renderer m_renderer;
	Shader m_shader;
	Line m_line;

	void Draw(int width, int height, ImGuiIO& io) override
	{
		m_renderer.Clear();

		m_shader.Bind();
		m_line.Draw(m_renderer, m_shader);
	}
};
