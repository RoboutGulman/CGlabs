#pragma once
#include "stdafx.h"

#include <vector>
#include <iostream>
#include <string>

class Controls
{
public:
	void Draw(std::vector<glm::vec2*> pointsPtr, ImGuiIO& io)
	{
		using namespace std::string_literals;

		ImGui::Begin("Bezier curve");
		for (int i = 0; i < pointsPtr.size(); i++)
		{
			ImGui::SliderFloat2(("P"s + std::to_string(i + 1)).c_str(), &pointsPtr[i]->x, 0.0f, 960.0f);
		}

		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
		ImGui::End();
	}
};