#include "ItemInfoPopup.h"


#include "Item.h"
#include "Rarity.h"
#include "../Opus/ShapeRenderer.h"
#include "../Opus/TextRenderer.h"

void ItemInfoPopup::Awake()
{
	auto& transform = GetTransform();

	auto& background = Instantiate(transform);

	background.GetTransform().SetScale(100, 200);
	background.AddComponent(ShapeRenderer(Shape::kSquare, {0.1f, 0.1f, 0.1f, 0.5f}, false));

	auto& title_background = Instantiate(transform);

	title_background.GetTransform().SetScale(100, 20);
	title_background_renderer_ = &title_background.AddComponent(ShapeRenderer(Shape::kSquare, kUniqueItemColor, false));


	auto& title = Instantiate(transform);
	title_renderer_ = &title.AddComponent(TextRenderer());
}

void ItemInfoPopup::SetItem(const Item& item) const
{
	Color title_color {};
	switch (item.rarity)
	{
		case Rarity::kNormal:
			title_color = kNormalItemColor;
			break;
		case Rarity::kMagic:
			title_color = kMagicItemColor;
			break;
		case Rarity::kRare:
			title_color = kRareItemColor;
			break;
		case Rarity::kUnique:
			title_color = kUniqueItemColor;
			break;
		case Rarity::kCurrency:
			title_color = kCurrencyItemColor;
			break;
	}

	title_background_renderer_->SetColor(title_color);

	title_renderer_->SetText(item.name);
}
