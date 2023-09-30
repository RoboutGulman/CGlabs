#pragma once
#include "stdafx.h"

#include "BaseWindow.h"
#include "Renderer.h"

#include "Controls.h"
#include "Primitives/Rectangle.h"

class Window : public BaseWindow
{
public:
	Window(int w, int h, const char* title)
		: BaseWindow(w, h, title)
		, m_shader("res/shaders/Basic.shader")
		, m_renderer()
		, m_rectangle(glm::vec3{ 0, 0, 0 }, w, h, glm::vec4{ 1.0 })

	{
		m_shader.Bind();
		glm::mat4 view = glm::mat4(1.0f);
		glm::mat4 projection = glm::ortho(0.0f, float(w), float(h), 0.0f, -1.0f, 100.0f);
		m_shader.SetUniformMatrix4fv("u_view", view);
		m_shader.SetUniformMatrix4fv("u_projection", projection);
	}

private:
	Renderer m_renderer;
	Shader m_shader;
	Rectangle m_rectangle;

	void Draw(int width, int height, ImGuiIO& io) override
	{
		m_renderer.Clear();

		m_shader.Bind();
		m_shader.SetUniform2f("resolution", 800, 600);

		m_rectangle.Draw(m_renderer, m_shader);
	}
};
