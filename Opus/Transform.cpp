#include "pch.h"
#include "Transform.h"

#include "BaseEntityRenderer.h"
#include "Core.h"

Transform::~Transform()
{
	// TODO Check why empty check needed
	if(parent_ && !parent_->children_.empty())
	{
		RemoveByValue(parent_->children_, this);
	}
}

// TODO Change to ref
void Transform::SetParent(Transform* transform)
{
	parent_ = transform;
	parent_->children_.push_back(this);
	RecalculateLocalPosition();
	entity_->RecalculateVisibility(transform);
}

void Transform::SetSize(const float width, const float height)
{
	scale_ = {width, height};

	origin_ = scale_ / 2;
	
	if(entity_->HasRenderer())
	{
		entity_->GetRenderer()->SetSize(width, height);
	}
}

Vector2 Transform::GetPosition() const
{
	return position_;
}

void Transform::SetPosition(const Vector2 position)
{
	position_ = position;
	RecalculateLocalPosition();
	
	// TODO Should only be recalculated once at end of frame
	RecalculateChildrenPosition();
}

void Transform::SetLocalPosition(Vector2 position)
{
	if(parent_)
	{
		SetPosition(parent_->position_ + position);
	}
	else
	{
		SetPosition(position);
	}
}

void Transform::Move(const Vector2 offset)
{
	SetPosition(position_ + offset);
}

void Transform::SetOrigin(const Vector2 origin)
{
	origin_ = origin;
}

Vector2 Transform::GetOrigin() const
{
	return origin_;
}

Vector2 Transform::GetScale() const
{
	return scale_;
}

void Transform::RecalculateLocalPosition()
{
	if(parent_)
	{
		local_position_ = position_ - parent_->position_;
	}
	else
	{
		local_position_ = position_;
	}
}

void Transform::RecalculateChildrenPosition()
{
	for (const auto& child : children_)
	{
		child->RecalculateChildPosition();
	}
}

void Transform::RecalculateChildPosition()
{
	position_ = parent_->position_ + local_position_;

	RecalculateChildrenPosition();
}