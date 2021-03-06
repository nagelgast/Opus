#include "pch.h"
#include "TextRenderer.h"

#include "BaseEntityRenderer.h"

void TextRenderer::Awake()
{
	renderer_ = entity_->CreateRenderer();
	renderer_->in_world_space_ = false;
}

void TextRenderer::SetText(const std::string& text) const
{
	renderer_->SetText(text.c_str());
}

float TextRenderer::GetWidth() const
{
	return renderer_->GetWidth();
}
