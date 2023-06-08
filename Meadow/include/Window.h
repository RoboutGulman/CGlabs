#pragma once
#include "stdafx.h"

#include "BaseWindow.h"
#include "Renderer.h"

#include "Primitives/Rectangle.h"
#include <Primitives/Circle.h>
#include "Cloud.h"
#include "Butterfly.h"

class Window : public BaseWindow
{
public:
	Window(int w, int h, const char* title)
		: BaseWindow(w, h, title)
		, m_shader("res/shaders/Basic.shader")
		, m_renderer()
		, m_ground({ 0, 0 }, w, h, { 0.01f, 0.95f, 0.01f, 1.0f })
		, m_sky({ 0, 0 }, w , h / 1.5, { 0.0f, 0.6f, 0.95f, 0.7f })
		, m_sun({ 0, 0 }, 100, 100, { 0.95f, 0.95f, 0.01f, 1.0f })
		, m_cloud({ 30, 30 }, 200, 50)
		, m_butterfly({ 400, 500 }, 200, 50)

	{
		m_shader.Bind();
		m_shader.SetUniformMatrix4fv("MVP", glm::ortho(0.0f, float(w), float(h), 0.0f, -1.0f, 100.0f));
	}

private:
	Renderer m_renderer;
	Shader m_shader;
	Rectangle m_ground;
	Rectangle m_sky;
	Circle m_sun;
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
