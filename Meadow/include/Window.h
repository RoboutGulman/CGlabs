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
		, m_time(glfwGetTime())
		, m_firstButtefly(glm::vec3{ 400, 500, 0 }, 50, 50, glm::vec4{ float(sin(m_time)), 0.95f, 0.7f, 1.0f }, glm::vec4{ float(cos(m_time)), 0.5f, 0.07f, 1.0f }, glm::vec4{ 0.5f, float(sin(m_time)), 0.7f, 1.0f }, 30)
		, m_secondButterfly(glm::vec3{ 100, 600, 0 }, 50, 50, glm::vec4{ 0.95f, float(sin(m_time)), 0.7f, 1.0f }, glm::vec4{ float(cos(m_time)), 0.5f, 0.07f, 1.0f }, glm::vec4{ 0.5f, float(cos(m_time)), 0.9f, 1.0f }, 120)
		, m_thirdButterfly(glm::vec3{ 600, 650, 0 }, 50, 50, glm::vec4{ 0.95f, float(sin(m_time)), 0.0f, 1.0f }, glm::vec4{ 0.5f, float(cos(m_time)), 0.07f, 1.0f }, glm::vec4{ 0.95f, float(sin(m_time)), 0.7f, 1.0f }, 120)
	{
		m_clouds.emplace_back(glm::vec3{ 300, 50, 0 }, 200, 50);
		m_clouds.emplace_back(glm::vec3{ 600, 150, 0 }, 100, 50);

		m_grasses.emplace_back(glm::vec3{ 100, 500, 0 }, 700, 60, 8, glm::vec4{ 0.26f, 0.6f, 0.3f, 1.0f });
		m_grasses.emplace_back(glm::vec3{ 50, 600, 0 }, 200, 60, 4, glm::vec4{ 0.0f, 0.3f, 0.0f, 1.0f });
		m_grasses.emplace_back(glm::vec3{ 600, 650, 0 }, 300, 60, 8, glm::vec4{ 0.075f, 0.53f, 0.03f, 1.0f });

		m_flowers.emplace_back(glm::vec3{ 400, 500, 0 }, 25, 50, 6, glm::vec4{ 1.f, 0.f, 0.f, 1.0f });
		m_flowers.emplace_back(glm::vec3{ 100, 600, 0 }, 25, 50, 6, glm::vec4{ 0.f, 0.f, 1.f, 1.0f });
		m_flowers.emplace_back(glm::vec3{ 600, 650, 0 }, 25, 50, 6, glm::vec4{ 0.f, 1.f, 1.f, 1.0f });

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
	Butterfly m_firstButtefly;
	Butterfly m_secondButterfly;
	Butterfly m_thirdButterfly;
	std::vector<Cloud> m_clouds;
	std::vector<Flower> m_flowers;
	std::vector<Grass> m_grasses;
	float m_time;

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
		m_firstButtefly.Draw(m_renderer, m_shader);
		m_secondButterfly.Draw(m_renderer, m_shader);
		m_thirdButterfly.Draw(m_renderer, m_shader);
	}
};
