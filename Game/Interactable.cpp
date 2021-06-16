#include "Interactable.h"

#include "PlayerController.h"

Rect Interactable::GetGlobalBounds()
{
	return bounds_.ConvertToGlobalSpace(entity_->GetTransform());
}
