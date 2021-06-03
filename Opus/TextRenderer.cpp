#include "pch.h"
#include "TextRenderer.h"

#include "BaseEntityRenderer.h"

void TextRenderer::Awake()
{
	renderer_ = entity_->CreateRenderer();
}

void TextRenderer::SetText(const std::string& text) const
{
	renderer_->SetText(text.c_str());
}

float TextRenderer::GetWidth()
{
	return renderer_->GetWidth();
}