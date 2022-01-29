#pragma once

#include <memory>

struct Input;
class Camera;
class Entity;
class BaseEntityRenderer;
class BaseCamera;

class BaseRenderer
{
public:
	virtual ~BaseRenderer() = default;

	virtual void CheckDebugState(const Input& input) = 0;
	virtual void Render() const = 0;
	virtual void SetCamera(const Camera& camera) = 0;
	virtual std::unique_ptr<BaseEntityRenderer> CreateEntityRendererInstance() const = 0;
};
