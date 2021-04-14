#include "pch.h"
#include "Entity.h"

#include <SFML/Graphics/Transformable.hpp>

#include "BaseRenderer.h"
#include "BaseEntityRenderer.h"
#include "Vector2.h"
#include "Component.h"
#include "EntityController.h"
#include "Shape.h"

#include "BaseTime.h"

Entity::Entity()
{
	transformable_ = std::make_unique<sf::Transformable>();
}

Entity::Entity(Entity& e) : layer_(e.layer_), shape_(e.shape_), ec_(e.ec_), transformable_(std::move(e.transformable_)), components_(e.components_)
{
	for (const auto& component : components_)
	{
		component.second->entity_ = this;
	}
}

Entity::~Entity()
{
	components_.clear();
}

void Entity::Start(EntityController* ec)
{
	ec_ = ec;
	for (const auto& component : components_)
	{
		component.second->Start();
	}

	if (renderer_)
	{
		const auto scale = transformable_->getScale();
		renderer_->SetSize(scale.x, scale.y);
	}
}

void Entity::Update()
{
	for (const auto& component : components_)
	{
		component.second->Update();
	}
}

void Entity::Destroy()
{
	ec_->DestroyEntity(*this);
}

std::shared_ptr<Entity> Entity::AddEntity(Entity&& e) const
{
	return ec_->AddEntity(std::move(e));
}

std::vector<std::shared_ptr<Entity>>& Entity::GetEntities() const
{
	return ec_->GetEntities();
}

float Entity::GetDeltaTime() const
{
	return ec_->GetTime().GetDeltaTime();
}

const Input& Entity::GetInput() const
{
	return ec_->GetInput();
}

void Entity::SetSize(float width, float height)
{
	transformable_->setScale(width, height);
	transformable_->setOrigin(width / 2.f, height / 2.f);

	if (renderer_)
	{
		renderer_->SetSize(width, height);
	}
}

void Entity::SetShape(Shape shape)
{
	shape_ = shape;
}

Vector2 Entity::GetPosition() const
{
	const auto position = transformable_->getPosition();
	return {position.x, position.y};
}

void Entity::SetPosition(float x, float y)
{
	transformable_->setPosition(x, y);
}

void Entity::SetPosition(Vector2 position)
{
	transformable_->setPosition(position.x, position.y);
}

BaseEntityRenderer* Entity::CreateRenderer()
{
	renderer_ = ec_->GetRenderer().CreateEntityRendererInstance();
	renderer_->entity_ = this;
	return renderer_.get();
}

bool Entity::HasRenderer() const
{
	return renderer_ != nullptr;
}

void Entity::Move(const Vector2 offset) const
{
	transformable_->move(offset.x, offset.y);
}

Vector2 Entity::GetOrigin() const
{
	const auto origin = transformable_->getOrigin();
	return {origin.x, origin.y};
}

BaseEntityRenderer* Entity::GetRenderer() const
{
	return renderer_.get();
}

Vector2 Entity::GetScale() const
{
	const auto scale = transformable_->getScale();
	return {scale.x, scale.y};
}
