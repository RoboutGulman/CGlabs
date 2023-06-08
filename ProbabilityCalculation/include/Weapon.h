#pragma once

#include "Traits.h"
#include <string>
#include <vector>
class Weapon
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

	std::string CalculateResult(int t, int sv)
	{
		int coutZeros = 0;
		int countOnes = 0;
		int countTwos = 0;
		int countThirds = 0;

		for (int rapidRoll = 1; rapidRoll < 7; rapidRoll++)
			for (int critRoll = 1; critRoll < 7; critRoll++)
				for (int firstWoundRoll = 1; firstWoundRoll < 7; firstWoundRoll++)
					for (int secondWoundRoll = 1; secondWoundRoll < 7; secondWoundRoll++)
						for (int thirdWoundRoll = 1; thirdWoundRoll < 7; thirdWoundRoll++)
						{
							std::vector<int> woundRolls = { firstWoundRoll, secondWoundRoll, thirdWoundRoll };
							for (int firstSaveRoll = 1; firstSaveRoll < 7; firstSaveRoll++)
								for (int secondSaveRoll = 1; secondSaveRoll < 7; secondSaveRoll++)
									for (int thirdSaveRoll = 1; thirdSaveRoll < 7; thirdSaveRoll++)
									{
										std::vector<int> saveRolls = { firstSaveRoll, secondSaveRoll, thirdSaveRoll };
										int result = Calculation(rapidRoll, critRoll, woundRolls, saveRolls, t, sv);
										if (result == 0)
										{
											coutZeros++;
										}
										if (result == 1)
										{
											countOnes++;
										}
										if (result == 2)
										{
											countTwos++;
										}
										if (result == 3)
										{
											countThirds++;
										}
									}
						}

		int sum = coutZeros + countOnes + countTwos + countThirds;
		return "veroiatnost is\n0 " + std::to_string(static_cast<double>(coutZeros) / sum) + "\n1 " + std::to_string(static_cast<double>(countOnes) / sum)
			+ "\n2 " + std::to_string(static_cast<double>(countTwos) / sum) + "\n3 " + std::to_string(static_cast<double>(countThirds) / sum);
	}

	int GetStr()
	{
		return m_str;
	}

	int GetAp()
	{
		return m_ap;
	}

	int GetRapidFire()
	{
		return m_rapidFireCount;
	}

	Traits GetTraits()
	{
		return m_traits;
	}

private:
	int m_str = 1, m_ap = 0, m_rapidFireCount = 0;
	Traits m_traits;

	bool weaponIsWounded(int t, int roll)
	{
		return (roll == 6) || (m_str * 2 > t && roll == 5) || (m_str >= t && roll == 4) || (m_str > t && roll == 3) || (m_str >= t * 2 && roll == 2); 
	}

	int Calculation(int rapidRoll, int critRoll, std::vector<int> woundRolls, std::vector<int> saveRolls, int t, int sv)
	{
		int numberOfShots = 1;
		int tempAp = m_ap;
		if (m_rapidFireCount)
		{
			if (rapidRoll == 6)
			{
				numberOfShots = 3;
			}
			else if (rapidRoll > 3)
			{
				numberOfShots = 2;
			}
		}
		int tempResult = 0;
		if (critRoll == 6)
		{
			if (m_traits.shred)
			{
				tempAp--;
			}
			if (m_traits.power)
			{
				tempAp = -7;
			}
			if (m_traits.shock)
			{
				if (numberOfShots == 1)
				{
					return 1;
				}
				else
				{
					numberOfShots--;
					tempResult++;
				}
			}
		}
		int S = m_str;
		int T = t;
		int totalSave = sv - tempAp;
		for (int i = 0; i < numberOfShots; i++)
		{
			int WOUND_ROLL = woundRolls[i];
			if (weaponIsWounded(T, WOUND_ROLL) && saveRolls[i] < totalSave)
			{
				tempResult++;
			}
		}
		return tempResult;
	}
};
