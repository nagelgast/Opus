#pragma once

#include "Rarity.h"
#include "../Opus/Core.h"

enum class Rarity;

class Item
{
public:
	void SetName(std::string name);
private:
	std::string name_;
	
	int width_ = 0;
	int height_ = 0;
	Rarity rarity_ = Rarity::kNormal;
};
