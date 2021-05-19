#include "InventoryItem.h"

#include <utility>

#include "Interactable.h"

InventoryItem::InventoryItem(std::shared_ptr<Item> item) : item_(std::move(item))
{
}
