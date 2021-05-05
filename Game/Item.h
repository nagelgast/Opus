#pragma once

#include "Rarity.h"
#include "../Opus/Core.h"
#include "../Opus/Sprite.h"

enum class Rarity;

class Item
{
public:
	void SetName(std::string name);
	Sprite GetSprite() const;
	void SetSprite(const Sprite& sprite);
private:
	std::string name_;
	Sprite sprite_;
	
	int width_ = 0;
	int height_ = 0;
	Rarity rarity_ = Rarity::kNormal;
};
