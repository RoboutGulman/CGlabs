#pragma once
#include "stdafx.h"

class ImGuiInitializer final
{
public:
	ImGuiInitializer(GLFWwindow* window)
	{
		ImGui::CreateContext();
		ImGui_ImplGlfw_InitForOpenGL(window, true);
		ImGui_ImplOpenGL3_Init("#version 100");
		ImGui::StyleColorsDark();
	}

	ImGuiInitializer(const ImGuiInitializer&) = delete;
	ImGuiInitializer& operator=(const ImGuiInitializer&) = delete;

	~ImGuiInitializer()
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}
};
