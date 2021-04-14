#pragma once

#include "Component.h"

enum class Shape;

class OPUS_API ShapeRenderer :
    public Component
{
public:
    ShapeRenderer(const Shape shape, float r, float g, float b, float a, bool in_world_space = true);
    void Start() override;
private:
    Shape shape_;
    float r_;
    float g_;
    float b_;
    float a_;
	bool in_world_space_;
};

