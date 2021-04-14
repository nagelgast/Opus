#pragma once

#include "Component.h"
#include <string>

class __declspec(dllexport) SpriteRenderer : public Component
{
public:
	SpriteRenderer(std::string path, int left, int top, int width, int height);
	void Start() override;
private:
	std::string path_;
	int left_;
	int top_;
	int width_;
	int height_;
};
