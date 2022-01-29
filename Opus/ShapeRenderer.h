#pragma once

#include "Color.h"
#include "Component.h"

enum class Shape;

class ShapeRenderer :
    public Component
{
public:
    ShapeRenderer(Shape shape, Color color);
	void SetColor(Color color);
    void Awake() override;
private:
    Shape shape_;
	Color color_;
	BaseEntityRenderer* renderer_ = nullptr;
};

