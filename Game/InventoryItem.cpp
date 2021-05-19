#include "InventoryItem.h"

#include <utility>

#include "Interactable.h"
#include "PlayerInventory.h"

InventoryItem::InventoryItem(std::shared_ptr<Item> item) : item_(std::move(item))
{
}
