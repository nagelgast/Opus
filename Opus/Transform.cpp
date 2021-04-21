#include "pch.h"
#include "Transform.h"

#include "BaseEntityRenderer.h"
#include "Entity.h"


void Transform::SetSize(float width, float height)
{
	scale_ = {width, height};

	if(entity_->HasRenderer())
	{
		entity_->GetRenderer()->SetSize(width, height);
	}
}

Vector2 Transform::GetPosition() const
{
	return position_;
}

void Transform::SetPosition(float x, float y)
{
	position_ = {x, y};
}

void Transform::SetPosition(Vector2 position)
{
	position_ = position;
}

void Transform::Move(Vector2 offset)
{
	position_ += offset;
}

Vector2 Transform::GetOrigin() const
{
	return origin_;
}


Vector2 Transform::GetScale() const
{
	return scale_;
}
