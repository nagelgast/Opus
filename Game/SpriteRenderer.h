#pragma once

#include "Component.h"
#include <string>

class SpriteRenderer : public Component
{
public:
	OPUS_API SpriteRenderer(std::string path, int left, int top, int width, int height);
	OPUS_API void Start() override;
private:
	std::string path_;
	int left_;
	int top_;
	int width_;
	int height_;
};
