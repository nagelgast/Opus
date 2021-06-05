#include "ItemInfoPopup.h"


#include "Item.h"
#include "Rarity.h"
#include "../Opus/ShapeRenderer.h"
#include "../Opus/TextRenderer.h"

const float kMargin = 10;

void ItemInfoPopup::Awake()
{
	auto& transform = GetTransform();

	auto& background = Instantiate(transform);

	background.GetTransform().SetScale(100, 200);
	background_renderer_ = &background.AddComponent(ShapeRenderer(Shape::kSquare, {0.1f, 0.1f, 0.1f, 0.5f}, false));


	auto& title_background = Instantiate(transform);

	title_background.GetTransform().SetScale(100, 30);
	title_background_renderer_ = &title_background.AddComponent(ShapeRenderer(Shape::kSquare, kUniqueItemColor, false));

	auto& title = Instantiate(transform);
	title_renderer_ = &title.AddComponent(TextRenderer());
}

void ItemInfoPopup::SetItem(const Item& item) const
{
	Color title_color {};
	switch (item.GetRarity())
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

	title_renderer_->SetText(item.GetName());
	const auto width = title_renderer_->GetWidth();

	Resize(*title_background_renderer_, width);
	Resize(*background_renderer_, width);
}

void ItemInfoPopup::Resize(ShapeRenderer& sr, const float width)
{
	auto& transform = sr.entity_->GetTransform();
	transform.SetScale(width + kMargin, transform.GetScale().y);
}
