#include "InventoryItem.h"

#include <utility>

InventoryItem::InventoryItem(std::shared_ptr<const Item> item) : item_(std::move(item))
{
}
