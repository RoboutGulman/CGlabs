#pragma once
#include "stdafx.h"

#include "BaseWindow.h"
#include "Renderer.h"
#include "Weapon.h"

#include "Target.h"
#include "utils.h"
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <map>
#include <sstream>
#include <string>

class Window : public BaseWindow
{
public:
	Window(int w, int h, const char* title)
		: BaseWindow(w, h, title)
		, m_renderer()
		, m_target()

	{
	}

private:
	Renderer m_renderer;
	Weapon m_weapon;
	Target m_target;
	std::string m_result = "";
	std::string m_alternateResult = "";
	std::vector<float> m_floatResult;
	float m_max = 1.0f;

	std::string GetResultFromMap(std::vector<float> vec)
	{
		using namespace std::string_literals;
		std::stringstream stream{};
		for (int i = 0; i < vec.size(); i++)
		{
			stream << "Wounds "s << i << ", chance "s << std::fixed << std::setprecision(2) << vec[i] * 100 << "%%"s
				   << " \n"s;
		}
		return stream.str();
	}

	void Draw(int width, int height, ImGuiIO& io) override
	{
		m_renderer.Clear();
		ImGui::Begin("Weapon effectiveness");

		auto targetCharacteristics = m_target.GetCharacteristicsPtr();
		for (auto& characteristic : targetCharacteristics)
		{
			ImGui::InputInt(characteristic.name.c_str(), characteristic.ptr);
		}

		auto weaponCharacteristics = m_weapon.GetCharacteristicsPtr();
		for (auto& characteristic : weaponCharacteristics)
		{
			ImGui::InputInt(characteristic.name.c_str(), characteristic.ptr);
		}

		/* auto traits = m_weapon.GetTraitsPtr();
		for (auto& trait : traits)
		{
			ImGui::Checkbox(trait.name.c_str(), trait.ptr);
		}

		if (ImGui::Button(("Calculate"), ImVec2(100, 30)))
		{
			m_result = m_weapon.CalculateResult(m_target.GetToughness(), m_target.GetSave()).c_str();
		}*/

		if (ImGui::Button(("Alternate Calculate"), ImVec2(100, 30)))
		{
			m_floatResult = CalculateChance(m_weapon.GetStr(), m_target.GetToughness(), m_target.GetSave(), m_weapon.GetAp(), m_weapon.GetRapidFire(), m_weapon.GetTraits());
			m_max = *max_element(std::begin(m_floatResult), std::end(m_floatResult));
			m_alternateResult = GetResultFromMap(m_floatResult).c_str();
		}

		ImGui::Text(m_result.c_str());
		ImGui::Text(m_alternateResult.c_str());
		if (m_floatResult.size() > 0)
		{
			ImGui::PlotHistogram("Histogram", &m_floatResult[0], m_floatResult.size(), 0, NULL, 0.0f, m_max, ImVec2(0, 80.0f));
		}

		ImGui::End();
	}
};
