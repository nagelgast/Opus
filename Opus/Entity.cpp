#include "pch.h"
#include "Entity.h"

#include "Transform.h"
#include "BaseRenderer.h"
#include "BaseEntityRenderer.h"
#include "Vector2.h"
#include "Component.h"
#include "EntityController.h"

#include "BaseTime.h"

Entity::Entity()
{
	transform_ = AddComponent<Transform>();
}

Entity::Entity(Entity& e) : layer_(e.layer_), shape_(e.shape_), ec_(e.ec_), transform_(std::move(e.transform_)), components_(e.components_)
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
		const auto scale = transform_->GetScale();
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

Transform& Entity::GetTransform()
{
	return *transform_;
}

void Entity::SetShape(Shape shape)
{
	shape_ = shape;
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

BaseEntityRenderer* Entity::GetRenderer() const
{
	return renderer_.get();
}
