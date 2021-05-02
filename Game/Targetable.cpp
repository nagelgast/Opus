#include "Targetable.h"


#include "TargetingSystem.h"
#include "../Opus/Input.h"

void Targetable::Start()
{
	for (auto entity : entity_->GetEntities())
	{
		auto ts = entity->GetComponent<TargetingSystem>();
		if (ts)
		{
			targeting_system_ = ts;
			break;
		}
	}
}

void Targetable::Update()
{
	const auto& input = entity_->GetInput();

	const auto dist = 5;
	auto m_pos = input.mouse_world_pos;
	auto pos = entity_->GetTransform().GetPosition();
	if(abs(pos.x - m_pos.x) < dist && abs(pos.y - m_pos.y) < dist)
	{
		targeting_system_->SetTarget(entity_->GetComponent<Targetable>());
	}
	
}

void Targetable::Interact()
{
	if(handler_)
	{
		handler_();
	}
}

void Targetable::SetHandler(std::function<void()> handler)
{
	handler_ = handler;
}
