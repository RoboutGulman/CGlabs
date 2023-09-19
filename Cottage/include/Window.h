#pragma once
#include "stdafx.h"

#include "BaseWindow.h"
#include "Renderer.h"

#include "CompoundObects/Cottage.h"
#include "Controls.h"
#include <Primitives/Skybox.h>
#include <ShaderMVPUniformMap.h>

const float SKYBOX_SIZE = 10.0f;

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
	const glm::vec3 LIGHT_COLOR{ 1.0f, 1.0f, 1.0f };
	const glm::vec3 LIGHT_POSITION{ 10.2f, 10.0f, 10.0f };

	void Draw(int width, int height, ImGuiIO& io) override
	{
		m_renderer.Clear();

		m_skyboxShader.Bind();
		m_skyboxShader.SetUniformMatrix4fv("MVP", m_controls.GetMVPMatrix(m_window, width, height));

		m_shader.Bind();
		m_shader.SetUniformMatrix4fv("MVP", m_controls.GetMVPMatrix(m_window, width, height));
		m_shader.SetUniform3f("u_lightColor", LIGHT_COLOR);
		m_shader.SetUniform3f("u_lightPos", LIGHT_POSITION);

		m_skybox.Draw(m_renderer, m_skyboxShader);
		m_cottage.Draw(m_renderer, m_shader);
	}

	std::vector<std::string> GetFaces()
	{
		return { "res\\assets\\skybox\\right.png",
			"res\\assets\\skybox\\left.png",
			"res\\assets\\skybox\\top.png",
			"res\\assets\\skybox\\bottom.png",
			"res\\assets\\skybox\\front.png",
			"res\\assets\\skybox\\back.png" };
	}
};
