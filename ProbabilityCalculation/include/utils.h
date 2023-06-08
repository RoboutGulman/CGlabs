#pragma once
#include <cmath>
#include <map>
#include <vector>

unsigned int factorial(unsigned int n)
{
	if (n == 0)
		return 1;
	return n * factorial(n - 1);
}

float BernoulliFormula(int n, int k, float p)
{
	return float(factorial(n)) / (factorial(k) * factorial(n - k)) * pow(p, k) * pow((1 - p), (n - k));
}

float GetDiceThrowChance(int difficulty)
{
	if (difficulty <= 0)
	{
		return 1.0f;
	}
	if (difficulty >= 7)
	{
		return 0.0f;
	}
	return (7.0f  - difficulty) / 6.0;
}

float GetToWoundChance(int t, int str)
{
	if (str >= t * 2)
	{
		return GetDiceThrowChance(2);
	}
	if (str > t)
	{
		return GetDiceThrowChance(3);
	}
	if (str == t)
	{
		return GetDiceThrowChance(4);
	}
	if (str <= t / 2)
	{
		return GetDiceThrowChance(6);
	}
	return GetDiceThrowChance(5);
}

float GetSaveChance(int sv, int ap)
{
	return GetDiceThrowChance(sv - ap);
}

struct ChanceOfNumberOfShots
{
	float chance;
	int numberOfShots;
};

std::vector<ChanceOfNumberOfShots> GetChanceOfNumberOfShots(int rapidFire)
{
	if (rapidFire == 0)
	{
		return { {0.0f, 0}, { 1.0f, 1 } };
	}
	if (rapidFire == 1)
	{
		return {
			{ 0.0f, 0 },
			{ 0.5f, 1 },
			{ 1.0f / 3, 2 },
			{ 1.0f / 6, 3 }
		};
	}
	if (rapidFire == 2)
	{
		return { { 0.0f, 0 }, { 0.0f, 1 }, { 0.25f, 2 }, { 1.0f / 3, 3 }, { 5.0f / 18, 4 }, { 1.0f / 9, 5 }, { 1.0f / 36, 6 } };
	}
	if (rapidFire == 3)
	{
		return {
			{ 0.0f, 0 },
			{ 0.0f, 1 },
			{ 0.0f, 2 },
			{ 1.0f / 8, 3 },
			{ 0.25f, 4 },
			{ 7.0f / 24, 5 },
			{ 11.0f / 54, 6 },
			{ 7.0f / 72, 7 },
			{ 1.0f / 36, 8 },
			{ 1.0f / 216, 9 }
		};
	}
	throw std::invalid_argument("received negative value");
}

std::vector<float> CalculateChance(int str, int t, int sv, int ap, int rapidFire, Traits traits)
{
	auto numberOfShots = GetChanceOfNumberOfShots(rapidFire);

	std::vector<float> result(numberOfShots.size() );

	for (auto& shotsAndChances : numberOfShots)
	{
		for (int i = 0; i <= shotsAndChances.numberOfShots; i++)
		{
			result[i] += shotsAndChances.chance * BernoulliFormula(shotsAndChances.numberOfShots, i, GetToWoundChance(t, str) * (1.0f - GetSaveChance(sv, ap)));
		}
	}
	return result;
}
