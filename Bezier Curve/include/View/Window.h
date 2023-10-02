#pragma once
#include "stdafx.h"

#include <iostream>

#include "BaseWindow.h"
#include "Renderer.h"
#include "Texture.h"
#include "VertexBuffer/DynamicVertexBuffer.h"
#include "VertexBuffer/StaticVertexBuffer.h"
#include "VertexBufferLayout.h"
#include <Primitives/BezierCurve.h>

#include "../Model/BezierCurveModel.h"

#include "BezierPoints.h"
#include "Controls.h"
#include "CoordinateSystem.h"
#include "DottedLines.h"


class Window : public BaseWindow
{
public:
	Window(int w, int h, const char* title, BezierCurvePoints points)
		: BaseWindow(w, h, title)
		, m_shader("res/shaders/Basic.shader")
		, m_renderer()
		, m_model(points)
		, m_bezierCurve({ 0.95f, 0.3f, 0.15f, 1.0f }, false)
		, m_bezierPoints()
		, m_coordinateSystem(w, h)
		, m_dottedLines(w, h)
		, m_controls()
	{
		m_shader.Bind();
		m_shader.SetUniformMatrix4fv("m_model", glm::mat4(1.0f));
		m_shader.SetUniformMatrix4fv("m_view", glm::mat4(1.0f));
		m_shader.SetUniformMatrix4fv("m_projection", glm::ortho(0.0f, float(w), float(h), 0.0f, -1.0f, 100.0f));
		m_shader.Unbind();
	}

private:
	Renderer m_renderer;
	Shader m_shader;

	BezierCurveModel m_model;

	CoordinateSystem m_coordinateSystem;
	BezierCurve m_bezierCurve;
	BezierPointsView m_bezierPoints;
	DottedLines m_dottedLines;
	Controls m_controls;

	void Draw(int width, int height, ImGuiIO& io) override
	{
		m_renderer.Clear();

		m_shader.Bind();
		m_coordinateSystem.Draw(m_renderer, m_shader);
		m_bezierCurve.Draw(m_renderer, m_shader, m_model.GetPoints());
		m_bezierPoints.Draw(m_renderer, m_shader, m_model.GetPoints().GetVector());
		m_dottedLines.Draw(m_renderer, m_model.GetPoints().GetVector());
		m_controls.Draw(m_model.GetPointsPtr(), io);
	}
};
