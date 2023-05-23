#pragma once
#include "stdafx.h"

#include <iostream>

#include "BaseWindow.h"
#include "Renderer.h"
#include "Texture.h"
#include "VertexBuffer/DynamicVertexBuffer.h"
#include "VertexBuffer/StaticVertexBuffer.h"
#include "VertexBufferLayout.h"

#include "../Model/BezierCurveModel.h"

#include "BezierCurve.h"
#include "BezierPoints.h"
#include "Controls.h"
#include "CoordinateSystem.h"
#include "DottedLines.h"

class Window : public BaseWindow
{
public:
	Window(int w, int h, const char* title, const glm::vec2& p1, const glm::vec2& p2, const glm::vec2& p3, const glm::vec2& p4)
		: BaseWindow(w, h, title)
		, m_shader("res/shaders/Basic.shader")
		, m_renderer()
		, m_model(p1, p2, p3, p4)
		, m_bezierCurve()
		, m_bezierPoints()
		, m_coordinateSystem(w, h)
		, m_dottedLines(w, h)
		, m_controls()
	{
		m_shader.Bind();
		m_shader.SetUniformMatrix4fv("m_model", glm::mat4(1.0f));
		m_shader.SetUniformMatrix4fv("m_view", glm::mat4(1.0f));
		m_shader.SetUniformMatrix4fv("m_projection", glm::ortho(0.0f, 1280.0f, 720.0f, 0.0f, -1.0f, 100.0f));
		m_shader.Unbind();
	}

private:
	Renderer m_renderer;
	Shader m_shader;

	BezierCurveModel m_model;

	CoordinateSystem m_coordinateSystem;
	BezierCurve m_bezierCurve;
	BezierPoints m_bezierPoints;
	DottedLines m_dottedLines;
	Controls m_controls;

	void Draw(int width, int height, ImGuiIO& io) override
	{
		m_renderer.Clear();

		m_shader.Bind();
		m_coordinateSystem.Draw(m_renderer, m_shader);
		m_bezierCurve.Draw(m_renderer, m_shader, m_model.GetPoints());
		m_bezierPoints.Draw(m_renderer, m_shader, m_model.GetPoints());
		m_dottedLines.Draw(m_renderer, m_model.GetPoints());
		m_controls.Draw(m_model.GetPointsPtr(), io);
	}
};
