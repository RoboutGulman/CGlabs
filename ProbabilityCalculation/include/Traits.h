#pragma once
#include <vector>
#include <string>
struct InputNameAndTraitPtr
{
	std::string name;
	bool* ptr;
};

struct Traits
{
	std::vector<InputNameAndTraitPtr> GetTraitsPtr()
	{
		return { { "shock", &shock }, { "shred", &shred }, { "power", &power } };
	}

	bool shock = false;
	bool shred = false;
	bool power = false;
};