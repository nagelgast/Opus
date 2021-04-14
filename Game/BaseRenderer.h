#pragma once

#include <memory>
#include <vector>

class Entity;
class BaseEntityRenderer;
class BaseCamera;

class BaseRenderer
{
public:
	virtual ~BaseRenderer() = default;
	virtual void Render(const std::vector<std::shared_ptr<Entity>>&) const = 0;
	virtual void SetCamera(BaseCamera& camera) = 0;
	virtual std::unique_ptr<BaseCamera> CreateCamera() const = 0;
	virtual std::unique_ptr<BaseEntityRenderer> CreateEntityRendererInstance() const = 0;
};
