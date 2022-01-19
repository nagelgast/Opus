#include "MouseSlot.h"

#include "Item.h"
#include "WorldItem.h"
#include "../Opus/Input.h"
#include "../Opus/SpriteRenderer.h"

void MouseSlot::Awake()
{
	renderer_ = &AddComponent(SpriteRenderer());
}

bool MouseSlot::SetItem(std::unique_ptr<Item> item)
{
	item_ = std::move(item);
	const auto& sprite = item_->GetSprite();
	renderer_->SetSprite(sprite, false);

	GetTransform().SetScale(2, 2);
	
	return true;
}

bool MouseSlot::TryDrop(const Vector2 position)
{
	if(HasItem())
	{
		if(can_drop_items_)
		{
			Drop(position);
		}
		else
		{
			// PromptDestroyItem();
		}

		return true;
	}

	return false;
}

std::unique_ptr<Item> MouseSlot::Take()
{
	Clear();
	return std::move(item_);
}

Item& MouseSlot::GetItem()
{
	return *item_;
}

bool MouseSlot::HasItem() const
{
	return item_ != nullptr;
}

void MouseSlot::Update()
{
	GetTransform().SetPosition(Game::GetInput().mouse_screen_pos);
}

void MouseSlot::Drop(const Vector2 position)
{
	auto& world_item = Create<WorldItem>(position);
	world_item.Initialize(std::move(item_));

	Clear();
}

void MouseSlot::Clear() const
{
	renderer_->ResetSprite();
	GetTransform().SetScale(1,1);
}
