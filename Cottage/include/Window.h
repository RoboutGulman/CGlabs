#pragma once
#include "stdafx.h"

#include "BaseWindow.h"
#include "Renderer.h"

#include "Controls.h"
#include "SnubDodecahedron.h"
#include <Primitives/Skybox.h>
#include <ShaderMVPUniformMap.h>

class Window : public BaseWindow
{
public:
	Window(int w, int h, const char* title)
		: BaseWindow(w, h, title)
		, m_controls()
		, m_skyboxShader("res/shaders/Skybox.shader")
		, m_renderer()
		, m_skybox(GetFaces())
	{
	}

private:
	Renderer m_renderer;
	Skybox m_skybox;
	Shader m_skyboxShader;
	Controls m_controls;

	void Draw(int width, int height, ImGuiIO& io) override
	{
		m_renderer.Clear();

		m_skyboxShader.Bind();
		m_skyboxShader.SetUniformMatrix4fv("MVP", m_controls.GetMVPMatrix(m_window, width, height));

		m_skybox.Draw(m_renderer, m_skyboxShader);
	}

	std::vector<std::string> GetFaces()
	{
		return { "include\\model\\assets\\skybox\\right.jpg",
			"include\\model\\assets\\skybox\\left.jpg",
			"include\\model\\assets\\skybox\\top.jpg",
			"include\\model\\assets\\skybox\\bottom.jpg",
			"include\\model\\assets\\skybox\\front.jpg",
			"include\\model\\assets\\skybox\\back.jpg" };
	}
};
