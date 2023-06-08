#pragma once

#include <string>
#include <vector>
struct Target
{
	Target(int toughness = 3, int save = 7)
		: m_tough(toughness)
		, m_save(save)
	{
	}
	struct InputNameAndCharacteristicPtr
	{
		std::string name;
		int* ptr;
	};
	std::vector<InputNameAndCharacteristicPtr> GetCharacteristicsPtr()
	{
		return { { "toughness", &m_tough }, { "save", &m_save } };
	}
	int GetToughness()
	{
		return m_tough;
	}
	int GetSave()
	{
		return m_save;
	}

private:
	int m_tough, m_save;
};
