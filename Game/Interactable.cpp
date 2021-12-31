#include "Interactable.h"

#include "PlayerController.h"

Rect Interactable::GetGlobalBounds() const
{
	return entity_->GetTransform().GetBounds(offset_, size_);
}
