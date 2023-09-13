#pragma once
#include "stdafx.h"

#include "BaseWindow.h"
#include "Renderer.h"

#include "Controls.h"
#include <Primitives/Skybox.h>
#include <ShaderMVPUniformMap.h>
#include "rooms/LivingRoom.h"

class Window : public BaseWindow
{
public:
	Window(int w, int h, const char* title)
		: BaseWindow(w, h, title)
		, m_controls()
		, m_skyboxShader("res/shaders/Skybox.shader")
		, m_shader("res/shaders/Basic.shader")
		, m_renderer()
		, m_skybox(GetFaces())
	{
	}

private:
	Renderer m_renderer;
	Skybox m_skybox;
	Shader m_skyboxShader;
	Shader m_shader;
	Controls m_controls;
	LivingRoom m_livingRoom;

	void Draw(int width, int height, ImGuiIO& io) override
	{
		m_renderer.Clear();

		m_skyboxShader.Bind();
		m_skyboxShader.SetUniformMatrix4fv("MVP", m_controls.GetMVPMatrix(m_window, width, height));
		m_shader.Bind();
		m_shader.SetUniformMatrix4fv("MVP", m_controls.GetMVPMatrix(m_window, width, height));

		//m_skybox.Draw(m_renderer, m_skyboxShader);
		m_livingRoom.Draw(m_renderer, m_shader);
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
