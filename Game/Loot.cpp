#include "Loot.h"


#include "Interactable.h"
#include "Item.h"
#include "ItemTag.h"
#include "WorldItem.h"
#include "../Opus/ShapeRenderer.h"

void Loot::OnDestroy()
{
	SpawnItem();
}

void Loot::SpawnItem() const
{
	const Sprite sprite{"Sprites/Driftwood_Wand_inventory_icon.png", {0, 0, 78, 234}};
	auto item = std::make_unique<Item>(Item{"TestWand", sprite, {1, 3}, {ItemTag::weapon}});
	const Sprite sprite2{"Sprites/Goldrim_inventory_icon.png", {0, 0, 156, 156}};
	auto item2 = std::make_unique<Item>(Item{"TestHelm", sprite2, {2, 2}, {ItemTag::helmet}});
	const Sprite sprite3{"Sprites/Chaos_Orb_inventory_icon.png", {0, 0, 78, 78}};
	auto item3 = std::make_unique<Item>(Item{"TestOrb", sprite3, {1, 1}});

	const auto pos = entity_->GetTransform().GetPosition();

	auto& world_item = entity_->Instantiate<WorldItem>(pos);
	world_item.Initialize(std::move(item));
	world_item.GetTransform().CenterOrigin();
	auto& world_item2 = entity_->Instantiate<WorldItem>(pos);
	world_item2.Initialize(std::move(item2));
	world_item2.GetTransform().CenterOrigin();
	auto& world_item3 = entity_->Instantiate<WorldItem>(pos);
	world_item3.Initialize(std::move(item3));
	world_item3.GetTransform().CenterOrigin();
}
