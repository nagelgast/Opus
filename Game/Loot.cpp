#include "Loot.h"


#include "Interactable.h"
#include "Item.h"
#include "ItemData.h"
#include "Rarity.h"
#include "WorldItem.h"
#include "../Opus/ShapeRenderer.h"

void Loot::Awake()
{
	// TODO Service system
	
	item_data_ = new ItemData();
}

void Loot::OnDestroy()
{
	SpawnItem();
}

void Loot::SpawnItem() const
{
	//const Sprite sprite{"Sprites/Driftwood_Wand_inventory_icon.png", {0, 0, 78, 234}};

	const auto wand_base = item_data_->GetBaseType("Driftwood_Wand");
	const auto wand_category = item_data_->GetCategory(wand_base.category);
	
	auto item = std::make_unique<Item>(Item{wand_base, wand_category, Rarity::kNormal});
	// const Sprite sprite2{"Sprites/Goldrim_inventory_icon.png", {0, 0, 156, 156}};
	// auto item2 = std::make_unique<Item>(Item{Rarity::kUnique, "Goldrim", sprite2, {2, 2}, {"helmet"}});
	// const Sprite sprite3{"Sprites/Chaos_Orb_inventory_icon.png", {0, 0, 78, 78}};
	// auto item3 = std::make_unique<Item>(Item{Rarity::kCurrency, "Chaos Orb", sprite3, {1, 1}});

	const auto pos = entity_->GetTransform().GetPosition();

	auto& world_item = entity_->Instantiate<WorldItem>(pos);
	world_item.Initialize(std::move(item));
	world_item.GetTransform().CenterOrigin();
	// auto& world_item2 = entity_->Instantiate<WorldItem>(pos);
	// world_item2.Initialize(std::move(item2));
	// world_item2.GetTransform().CenterOrigin();
	// auto& world_item3 = entity_->Instantiate<WorldItem>(pos);
	// world_item3.Initialize(std::move(item3));
	// world_item3.GetTransform().CenterOrigin();
}
