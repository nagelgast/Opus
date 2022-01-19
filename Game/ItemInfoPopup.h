#pragma once

#include "../Opus/Color.h"
#include "../Opus/Core.h"

class Item;
class TextRenderer;
class ShapeRenderer;

constexpr Color kNormalItemColor = {0.78f,0.78f,0.78f};			// 200 200 200
constexpr Color kMagicItemColor = { 0.53f,0.53f,1};				// 136 136 255
constexpr Color kRareItemColor = { 1,1,0.47f};					// 255 255 119
constexpr Color kUniqueItemColor = { 0.69f, 0.38f, 0.15f};		// 175  96  37
constexpr Color kCurrencyItemColor = { 0.67f, 0.62f, 0.51f};		// 170 158 130

class ItemInfoPopup : public Component
{
public:
	void Awake() override;
	void SetItem(const Item& item) const;
private:
	static void Resize(const ShapeRenderer& sr, float width);

	ShapeRenderer* background_renderer_ = nullptr;
	ShapeRenderer* title_background_renderer_ = nullptr;
	TextRenderer* title_renderer_ = nullptr;
	TextRenderer* info_renderer_ = nullptr;
};

