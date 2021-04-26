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

Entity::Entity(Entity& e)
:	ec_(e.ec_),
	transform_(std::move(e.transform_)),
	collider_(e.collider_),
	components_(e.components_)
{
	for (const auto& component : components_)
	{
		component.second->entity_ = this;
	}
}

Entity::~Entity()
{
	if(ec_ && collider_)
	{
		ec_->collision_system_.RemoveCollider(collider_);
	}
	
	components_.clear();
}

void Entity::Start(EntityController* ec)
{
	ec_ = ec;
	for (const auto& component : components_)
	{
		component.second->Start();
	}

	if (collider_)
	{
		ec_->collision_system_.AddCollider(collider_);
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

	// TODO Handle in entity controller
	if(destroyed_)
	{
		ec_->DestroyEntity(*this);
	}
}

void Entity::FixedUpdate()
{
	for (const auto& component : components_)
	{
		component.second->FixedUpdate();
	}
}

void Entity::Destroy()
{
	destroyed_ = true;
}

std::shared_ptr<Collider> Entity::AddComponent(const Collider& c)
{
	collider_ = AddComponent<Collider>(c);
	return collider_;
}

std::shared_ptr<Entity> Entity::Instantiate() const
{
	return ec_->CreateEntity();
}

std::shared_ptr<Entity> Entity::Instantiate(Entity&& e) const
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

float Entity::GetFixedDeltaTime() const
{
	return ec_->GetTime().GetFixedDeltaTime();
}

const Input& Entity::GetInput() const
{
	return ec_->GetInput();
}

Transform& Entity::GetTransform() const
{
	return *transform_;
}

void Entity::SetName(const std::string& name)
{
	name_ = name;
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

void Entity::OnCollision(const Collider& other)
{
	for (const auto& component : components_)
	{
		component.second->OnCollision(other);
	}
}

BaseEntityRenderer* Entity::GetRenderer() const
{
	return renderer_.get();
}
