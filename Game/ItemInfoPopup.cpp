#include "ItemInfoPopup.h"


#include "Item.h"
#include "Rarity.h"
#include "Stat.h"
#include "../Opus/ShapeRenderer.h"
#include "../Opus/TextRenderer.h"

const float kMargin = 10;

void ItemInfoPopup::Awake()
{
	auto& background = CreateChild();
	background.GetTransform().SetScale(100, 200);
	background_renderer_ = &background.AddComponent(ShapeRenderer(Shape::kSquare, {0.1f, 0.1f, 0.1f, 0.5f}, false));


	auto& title_background = CreateChild();
	title_background.GetTransform().SetScale(100, 30);
	title_background_renderer_ = &title_background.AddComponent(ShapeRenderer(Shape::kSquare, kUniqueItemColor, false));

	auto& title = CreateChild();
	title_renderer_ = &title.AddComponent(TextRenderer());

	auto& info = CreateChild();
	info.GetTransform().SetLocalPosition({0, 30});
	info_renderer_ = &info.AddComponent(TextRenderer());
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
	const auto title_width = title_renderer_->GetWidth();

	const auto info_text = item.GenerateText();
	info_renderer_->SetText(info_text);

	const auto info_width = info_renderer_->GetWidth();

	const auto width = std::max(title_width, info_width);
	
	Resize(*title_background_renderer_, width);
	Resize(*background_renderer_, width);
}

void ItemInfoPopup::Resize(ShapeRenderer& sr, const float width)
{
	auto& transform = sr.entity_->GetTransform();
	transform.SetScale(width + kMargin, transform.GetScale().y);
}
