#pragma once

#include <memory>
#include <vector>

class Camera;
class Entity;
class BaseEntityRenderer;
class BaseCamera;

class BaseRenderer
{
public:
	virtual ~BaseRenderer() = default;
	
	virtual void Render(const std::vector<std::shared_ptr<Entity>>&) const = 0;
	virtual void SetCamera(const Camera& camera) = 0;
	virtual std::unique_ptr<BaseEntityRenderer> CreateEntityRendererInstance() const = 0;
};
