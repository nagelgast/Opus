#include "pch.h"
#include "EntityHierarchyUI.h"

#include "TextRenderer.h"
#include "Transform.h"

void EntityHierarchyUI::Awake()
{
	text_renderer_ = &AddComponent(TextRenderer());
}

void EntityHierarchyUI::Update()
{
	UpdateText();
}

void EntityHierarchyUI::UpdateText()
{
	text_.clear();
	
	for (const auto& child : GetEntities())
	{
		if(child->GetTransform().GetParent() == nullptr)
		{
			ParseEntity(*child);
		}
	}

	text_renderer_->SetText(text_);
}

void EntityHierarchyUI::ParseEntity(const Entity& entity)
{
	if (depth_ > 0)
	{
		text_ += std::string(depth_, ' ');
		text_ += "|-";
	}

	auto name = entity.GetName();
	if(name.empty())
	{
		name = "Entity";
	}
	text_ += name;
	text_ += "\n";

	auto children = entity.GetTransform().GetChildren();
	if(!children.empty())
	{
		depth_++;
		for (const auto& child : children)
		{
			ParseEntity(*child->entity_);
		}
		depth_--;
	}
}


