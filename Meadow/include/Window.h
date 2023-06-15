#pragma once
#include "stdafx.h"

#include "BaseWindow.h"
#include "Renderer.h"

#include "Butterfly.h"
#include "Cloud.h"
#include "Flower.h"
#include "Grass.h"
#include "Primitives/Rectangle.h"
#include <Primitives/Ellipse.h>
#include <vector>

class Window : public BaseWindow
{
public:
	Window(int w, int h, const char* title)
		: BaseWindow(w, h, title)
		, m_shader("res/shaders/Basic.shader")
		, m_renderer()
		, m_ground({ 0, 0, 0 }, w, h, { 0.01f, 0.95f, 0.01f, 1.0f })
		, m_sky({ 0, 0, 0 }, w, h / 1.5, { 0.0f, 0.6f, 0.95f, 0.7f })
		, m_sun({ 200, 100, 0 }, 100, 100, { 0.95f, 0.95f, 0.01f, 1.0f })

	{
		m_butterflies.emplace_back(glm::vec3{ 400, 500, 0 }, 50, 50, glm::vec4{ 0.95f, 0.2f, 0.2f, 1.0f }, 30);
		m_clouds.emplace_back(glm::vec3{ 300, 50, 0 }, 200, 50);
		m_grasses.emplace_back(glm::vec3{ 100, 500, 0 }, 700, 60, 8, glm::vec4{ 0.26f, 0.6f, 0.3f, 1.0f });
		m_flowers.emplace_back(glm::vec3{ 300, 500, 0 }, 25, 50, 6, glm::vec4{ 0.f, 0.f, 1.f, 1.0f });

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
	std::vector<Cloud> m_clouds;
	std::vector<Butterfly> m_butterflies;
	std::vector<Flower> m_flowers;
	std::vector<Grass> m_grasses;

	void Draw(int width, int height, ImGuiIO& io) override
	{
		m_renderer.Clear();

		m_shader.Bind();
		m_ground.Draw(m_renderer, m_shader);
		m_sky.Draw(m_renderer, m_shader);
		m_sun.Draw(m_renderer, m_shader);
		for (auto& cloud : m_clouds)
		{
			cloud.Draw(m_renderer, m_shader);
		}
		for (auto& grass : m_grasses)
		{
			grass.Draw(m_renderer, m_shader);
		}
		for (auto& flower : m_flowers)
		{
			flower.Draw(m_renderer, m_shader);
		}
		for (auto& butterfly : m_butterflies)
		{
			butterfly.Draw(m_renderer, m_shader);
		}
	}
};
