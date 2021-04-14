#pragma once

#include "BaseCamera.h"
#include <SFML/Graphics/View.hpp>

class SFMLCamera :
    public BaseCamera
{
public:
    virtual const Vector2& GetPosition() override;
private:
    virtual void SetPosition(const Vector2 position) override;
    Vector2 position_;
};
