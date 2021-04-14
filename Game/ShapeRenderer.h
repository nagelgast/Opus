#pragma once

#include "Component.h"

enum class Shape;

class __declspec(dllexport) ShapeRenderer :
    public Component
{
public:
    ShapeRenderer(const Shape shape, float r, float g, float b, float a);
    void Start() override;
private:
    Shape shape_;
    float r_;
    float g_;
    float b_;
    float a_;
};

