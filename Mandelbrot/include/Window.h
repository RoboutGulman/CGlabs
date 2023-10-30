#pragma once

#include "BaseWindow.h"
#include "Controls.h"
#include "Renderer.h"
#include "TexturedPrimitives/TexturedRectangle.h"

class Window : public BaseWindow
{
public:
	Window(int w, int h, const char* title);

private:
	Renderer m_renderer;
	Shader m_shader;
	TexturedRectangle m_mandelbrot;
	Controls m_controls;

	void Draw(int width, int height, ImGuiIO& io) override;

	void Move();
	void ZoomWindow();
	void UnzoomWindow();
};
