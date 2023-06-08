#pragma once
#include "stdafx.h"

#include "ImGuiInitializer.h"
#include <iostream>
#include <stdexcept>

class BaseWindow
{
public:
	BaseWindow(int w, int h, const char* title)
		: m_window{ CreateWindow(w, h, title) }
	{
		if (!m_window)
		{
			glfwTerminate();
			throw std::runtime_error("Failed to create window");
		}
		glfwMakeContextCurrent(m_window);
		glfwSwapInterval(1);

		if (glewInit() != GLEW_OK)
		{
			std::cout << "Error" << std::endl;
		}
		//glEnable(GL_DEPTH_TEST);
		//glDepthFunc(GL_LESS);
	}
	BaseWindow(const BaseWindow&) = delete;
	BaseWindow& operator=(const BaseWindow&) = delete;

	virtual ~BaseWindow()
	{
		glfwDestroyWindow(m_window);
	}

	void Run()
	{
		ImGuiInitializer imGui(m_window);
		ImGuiIO& io = ImGui::GetIO();
		(void)io;
		ImGui::SetNextWindowSize(ImVec2(400, 500));
		while (!glfwWindowShouldClose(m_window))
		{
			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplGlfw_NewFrame();
			ImGui::NewFrame();

			int w, h;
			glfwGetFramebufferSize(m_window, &w, &h);
			Draw(w, h, io);

			ImGui::Render();
			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

			glfwSwapBuffers(m_window);
			glfwPollEvents();
		}
	}

protected:
	GLFWwindow* m_window;

private:
	virtual void Draw(int width, int height, ImGuiIO& io) = 0;

	static GLFWwindow* CreateWindow(int w, int h, const char* title)
	{
		return glfwCreateWindow(w, h, title, NULL, NULL);
	}
};
