#pragma once
#include "stdafx.h"

#include "BaseWindow.h"
#include "Renderer.h"

#include "Butterfly.h"
#include "Cloud.h"
#include "Primitives/Rectangle.h"
#include <Primitives/Ellipse.h>

class Window : public BaseWindow
{
public:
	Window(int w, int h, const char* title)
		: BaseWindow(w, h, title)
		, m_shader("res/shaders/Basic.shader")
		, m_renderer()
		, m_ground({ 0, 0, 0 }, w, h, { 0.01f, 0.95f, 0.01f, 1.0f })
		, m_sky({ 0, 0, 0 }, w, h / 1.5, { 0.0f, 0.6f, 0.95f, 0.7f })
		, m_sun({ 0, 0, 0 }, 100, 100, { 0.95f, 0.95f, 0.01f, 1.0f })
		, m_cloud({ 30, 30, 0 }, 200, 50)
		, m_butterfly({ 400, 500, 0 }, 50, 50, { 0.95, 0.2, 0.2, 1.0 }, 30)

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
	Rectangle m_ground;
	Rectangle m_sky;
	Ellipse m_sun;
	Cloud m_cloud;
	Butterfly m_butterfly;

	void Draw(int width, int height, ImGuiIO& io) override
	{
		m_renderer.Clear();

		m_shader.Bind();
		m_ground.Draw(m_renderer, m_shader);
		m_sky.Draw(m_renderer, m_shader);
		m_sun.Draw(m_renderer, m_shader);
		m_cloud.Draw(m_renderer, m_shader);
		m_butterfly.Draw(m_renderer, m_shader);
	}
};
