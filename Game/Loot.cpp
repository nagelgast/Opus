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
	const auto& wand_base = item_data_->GetBaseType("Driftwood_Wand");
	const auto wand_category = item_data_->GetCategory(wand_base.category);
	auto item = std::make_unique<Item>(Item{wand_base, wand_category, Rarity::kNormal, {23,325,16,52}});

	const auto& book_base = item_data_->GetBaseType("Book");
	const auto book_category = item_data_->GetCategory(book_base.category);
	auto item2 = std::make_unique<Item>(Item{book_base, book_category, Rarity::kCurrency, {102, 261, 19, 20}});

	const auto pos = entity_->GetTransform().GetPosition();

	// auto& world_item = CreateHere<WorldItem>();
	// world_item.Initialize(std::move(item));
	// auto& world_item2 = CreateHere<WorldItem>();
	// world_item2.Initialize(std::move(item2));
	// auto& world_item3 = entity_->Instantiate<WorldItem>(pos);
	// world_item3.Initialize(std::move(item3));
}
