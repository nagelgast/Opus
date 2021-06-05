#pragma once
#include <string>
#include <vector>

struct ItemCategory
{
	std::string name;
	int width = 1;
	int height = 1;

	std::vector<std::string> tags;
};
