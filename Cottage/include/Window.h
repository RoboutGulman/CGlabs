#pragma once
#include "stdafx.h"

#include "BaseWindow.h"
#include "Renderer.h"

#include "Controls.h"
#include "rooms/LivingRoom.h"
#include <Primitives/Skybox.h>
#include <ShaderMVPUniformMap.h>
#include "Cottage.h"

const float SKYBOX_SIZE = 8.0f;

class Window : public BaseWindow
{
public:
	Window(int w, int h, const char* title)
		: BaseWindow(w, h, title)
		, m_controls()
		, m_skyboxShader("res/shaders/Skybox.shader")
		, m_shader("res/shaders/Basic.shader")
		, m_renderer()
		, m_skybox(SKYBOX_SIZE, GetFaces())
	{
	}

private:
	Renderer m_renderer;
	Skybox m_skybox;
	Shader m_skyboxShader;
	Shader m_shader;
	Controls m_controls;
	Cottage m_cottage;

	void Draw(int width, int height, ImGuiIO& io) override
	{
		m_renderer.Clear();

		m_skyboxShader.Bind();
		m_skyboxShader.SetUniformMatrix4fv("MVP", m_controls.GetMVPMatrix(m_window, width, height));
		m_shader.Bind();
		m_shader.SetUniformMatrix4fv("MVP", m_controls.GetMVPMatrix(m_window, width, height));
		m_shader.SetUniform3f("u_lightColor", glm::vec3(1.0f, 1.0f, 1.0f));
		m_shader.SetUniform3f("u_lightPos", glm::vec3(10.2f, 10.0f, 10.0f));

		m_skybox.Draw(m_renderer, m_skyboxShader);
		m_cottage.Draw(m_renderer, m_shader);
	}

	std::vector<std::string> GetFaces()
	{
		return { "include\\model\\assets\\skybox\\right.png",
			"include\\model\\assets\\skybox\\left.png",
			"include\\model\\assets\\skybox\\top.png",
			"include\\model\\assets\\skybox\\bottom.png",
			"include\\model\\assets\\skybox\\front.png",
			"include\\model\\assets\\skybox\\back.png" };
	}
};
