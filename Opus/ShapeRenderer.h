#pragma once

#include "Color.h"
#include "Component.h"

enum class Shape;

class ShapeRenderer :
    public Component
{
public:
    ShapeRenderer(Shape shape, Color color, bool in_world_space = true);
	void SetColor(Color color);
    void Start() override;
private:
    Shape shape_;
	Color color_;
	bool in_world_space_;
	BaseEntityRenderer* renderer_ = nullptr;
};

