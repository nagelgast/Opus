#include "pch.h"
#include "Entity.h"

#include <iostream>

#include "Transform.h"
#include "BaseRenderer.h"
#include "BaseEntityRenderer.h"
#include "Vector2.h"
#include "Component.h"
#include "EntityController.h"

#include "BaseTime.h"
#include "CircleCollider.h"
#include "Game.h"
#include "RectCollider.h"

Entity::Entity()
{
	transform_ = &AddComponent(Transform());
}

Entity::~Entity()
{
	components_.clear();
}

void Entity::Start() const
{
	for (const auto& component : components_)
	{
		component.second->Start();
	}
}

void Entity::Update() const
{
	for (const auto& component : components_)
	{
		component.second->Update();
	}
}

void Entity::FixedUpdate() const
{
	for (const auto& component : components_)
	{
		component.second->FixedUpdate();
	}
}

void Entity::AwakeComponent(const std::type_index type)
{
	components_[type]->Awake();
}

void Entity::Destroy()
{
	destroyed_ = true;
	for (const auto* child : transform_->children_)
	{
		child->entity_->Destroy();
	}
	OnDestroy();
}

RectCollider& Entity::AddComponent(const RectCollider& c)
{
	collider_ = &AddComponent<RectCollider>(c);
	return dynamic_cast<RectCollider&>(*collider_);
}

CircleCollider& Entity::AddComponent(const CircleCollider& c)
{
	collider_ = &AddComponent<CircleCollider>(c);
	return dynamic_cast<CircleCollider&>(*collider_);
}

float Entity::GetDeltaTime() const
{
	return Game::GetTime().GetDeltaTime();
}

float Entity::GetFixedDeltaTime() const
{
	return Game::GetTime().GetFixedDeltaTime();
}

Transform& Entity::GetTransform() const
{
	return *transform_;
}

std::string Entity::GetName() const
{
	return name_;
}

void Entity::SetName(const std::string& name)
{
	name_ = name;
}

void Entity::SetVisible(const bool value)
{
	visible_ = value;

	RecalculateChildVisibility();
}

BaseEntityRenderer* Entity::CreateRenderer()
{
	renderer_ = Game::GetRenderer().CreateEntityRendererInstance();
	renderer_->entity_ = this;
	return renderer_.get();
}

bool Entity::ShouldRender() const
{
	return HasRenderer() && visible_ && parent_visible_;
}

bool Entity::HasRenderer() const
{
	return renderer_ != nullptr;
}

void Entity::OnCollision(const Collider& other) const
{
	for (const auto& component : components_)
	{
		component.second->OnCollision(other);
	}
}

void Entity::OnDestroy() const
{
	for (const auto& component : components_)
	{
		component.second->OnDestroy();
	}
}

BaseEntityRenderer* Entity::GetRenderer() const
{
	return renderer_.get();
}

void Entity::RecalculateVisibility(const Transform& parent)
{
	parent_visible_ = parent.entity_->visible_ && parent.entity_->parent_visible_;
}

void Entity::RecalculateChildVisibility() const
{
	for (auto* child : transform_->children_)
	{
		child->entity_->RecalculateVisibility(*transform_);
		child->entity_->RecalculateChildVisibility();
	}
}
