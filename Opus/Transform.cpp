#include "pch.h"
#include "Transform.h"

#include "Core.h"

Transform::~Transform()
{
	// TODO Investigate why checks are needed
	if(parent_ && !parent_->children_.empty() && Contains(parent_->children_, this))
	{
		RemoveByValue(parent_->children_, this);
	}
}

Transform* Transform::GetParent()
{
	return parent_;
}

void Transform::SetParent(Transform& transform)
{
	parent_ = &transform;
	parent_->children_.push_back(this);
	
	RecalculateLocalPosition();
	RecalculateLocalScale();
	
	entity_->RecalculateVisibility(transform);
	entity_->RecalculateChildVisibility();
}

Vector2 Transform::GetPosition() const
{
	return position_;
}

void Transform::SetPosition(const Vector2 position)
{
	position_ = position;
	RecalculateLocalPosition();
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

void Transform::SetScale(const float width, const float height)
{
	scale_ = {width, height};
	RecalculateLocalScale();
	RecalculateChildrenScale();
}

Vector2 Transform::GetScale() const
{
	return scale_;
}

Rect Transform::GetBounds(const Vector2 offset, const Vector2 scale_multiplier) const
{
	// TODO Cache this
	const auto width = scale_.x * scale_multiplier.x;
	const auto height = scale_.y * scale_multiplier.y;

	const Rect bounds
	{
		position_.x + offset.x - width * 0.5f,
		position_.y + offset.y - height * 0.5f,
		width,
		height
	};

	return bounds;
}

std::vector<Transform*> Transform::GetChildren()
{
	return children_;
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

void Transform::RecalculateLocalScale()
{
	if(parent_)
	{
		local_scale_ = {scale_.x / parent_->scale_.x, scale_.y / parent_->scale_.y};
	}
	else
	{
		local_scale_ = scale_;
	}
}

void Transform::RecalculateChildrenScale()
{
	for (const auto& child : children_)
	{
		child->RecalculateChildScale();
	}
}

void Transform::RecalculateChildScale()
{
	scale_ = {parent_->scale_.x * local_scale_.x, parent_->scale_.y * local_scale_.y};

	RecalculateChildrenScale();
}