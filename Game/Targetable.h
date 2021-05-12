#pragma once

#include <functional>

#include "../Opus/Core.h"

class TargetingSystem;

class Targetable :
    public Component
{
public:
	void Start() override;
	void Update() override;
	void Interact();
	Event OnInteract;
private:
	std::shared_ptr<TargetingSystem> targeting_system_;
	std::function<void()> handler_;
};

