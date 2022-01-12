#pragma once

#include "Component.h"
#include "Particle.h"
#include "ParticleSettings.h"

class ParticleSystem :
    public Component
{
public:
	explicit ParticleSystem(ParticleSettings settings) : settings_(std::move(settings)){}

    void Awake() override;
    void Update() override;

private:
    void Finish();

    BaseEntityRenderer* renderer_ = nullptr;
    const ParticleSettings settings_;
    std::vector<Particle> particles_;
    bool playing_ = false;
    float remaining_duration_ = 0;
};
