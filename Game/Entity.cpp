#include "Entity.h"

#include "BaseRenderer.h"
#include "BaseEntityRenderer.h"
#include "Vector2.h"
#include "Component.h"
#include "EntityController.h"
#include "Shape.h"

#include "BaseTime.h"

Entity::Entity(Entity& e) : Transformable(e), layer_(e.layer_), shape_(e.shape_), ec_(e.ec_), components_(e.components_)
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
		auto scale = getScale();
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
	setScale(width, height);
	setOrigin(width / 2.f, height / 2.f);

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
	return getPosition();
}

void Entity::SetPosition(float x, float y)
{
	setPosition(x, y);
}

void Entity::SetPosition(Vector2 position)
{
	setPosition(position.x, position.y);
}

BaseEntityRenderer* Entity::CreateRenderer()
{
	renderer_ = ec_->GetRenderer().CreateEntityRendererInstance();
	renderer_->entity_ = this;
	return renderer_.get();
}

bool Entity::HasRenderer()
{
	return renderer_ != nullptr;
}

void Entity::Move(Vector2 offset)
{
	move(offset.x, offset.y);
}

Vector2 Entity::GetOrigin() const
{
	return getOrigin();
}

BaseEntityRenderer* Entity::GetRenderer() const
{
	return renderer_.get();
}

Vector2 Entity::GetScale() const
{
	return getScale();
}
