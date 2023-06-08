#pragma once
#include "Traits.h"
#include <vector>
#include <string>
class AlternateWeapon
{
public:
	struct InputNameAndCharacteristicPtr
	{
		std::string name;
		int* ptr;
	};
	std::vector<InputNameAndCharacteristicPtr> GetCharacteristicsPtr()
	{
		return { { "str", &m_str }, { "ap", &m_ap }, { "rapidFire", &m_rapidFireCount } };
	}

	std::vector<InputNameAndTraitPtr> GetTraitsPtr()
	{
		return m_traits.GetTraitsPtr();
	}

	int GetStr()
	{
		return m_str;
	}

	int GetAp()
	{
		return m_ap;
	}

private:
	int m_str = 1, m_ap = 0, m_rapidFireCount = 0;
	Traits m_traits;
};