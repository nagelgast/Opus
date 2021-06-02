#include "ItemInfoPopup.h"

#include "../Opus/ShapeRenderer.h"

void ItemInfoPopup::Awake()
{
	auto& transform = GetTransform();

	auto& background = Instantiate(transform);

	background.GetTransform().SetScale(100, 200);
	background.AddComponent(ShapeRenderer(Shape::kSquare, {0.1f, 0.1f, 0.1f, 0.5f}, false));

	auto& title_background = Instantiate(transform);

	title_background.GetTransform().SetScale(100, 20);
	title_background.AddComponent(ShapeRenderer(Shape::kSquare, { 0.68f, 0.38f, 0.15f, 0.5f }, false));

}

void ItemInfoPopup::SetItem(const Item& item)
{
}
