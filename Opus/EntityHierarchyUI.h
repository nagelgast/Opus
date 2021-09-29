#pragma once
#include "Entity.h"
#include "TextRenderer.h"

class EntityHierarchyUI : public Entity
{
public:
	void Awake() override;
	void Update() override;
private:
	void UpdateText();
	void ParseEntity(const Entity& entity);
	
	std::string text_;
	int depth_ = 0;
	
	Entity* root_ = nullptr;
	TextRenderer* text_renderer_ = nullptr;
};

