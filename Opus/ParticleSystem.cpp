#include "pch.h"

#include "ParticleSystem.h"
#include "BaseEntityRenderer.h"
#include "Game.h"
#include "Transform.h"

#include <math.h>

void ParticleSystem::Awake()
{
	renderer_ = entity_->CreateRenderer();
	const auto texture = Game::GetTextureManager().Get(settings_.sprite.path);
	renderer_->SetTexture(*texture);
	renderer_->SetParticles(settings_);

	particles_.resize(settings_.particle_count);
	const auto pos = entity_->GetTransform().GetPosition();
	for (auto& particle : particles_)
	{
		particle.position = pos;

		// TODO Make a utility function for generating a random angle
		const float angle = float(rand()) / RAND_MAX;
		// TODO Make a utility function for PI
		const auto radians = angle * 2 * 3.14159f;
		particle.velocity.x = cosf(radians) * settings_.speed;
		particle.velocity.y = sinf(radians) * settings_.speed;
	}

	remaining_duration_ = settings_.duration;

	if(settings_.auto_play)
	{
		playing_ = true;
	}
}

void ParticleSystem::Update()
{
	if(!playing_) return;

	const auto& dt = entity_->GetDeltaTime();

	for(auto& particle : particles_)
	{
		particle.position += particle.velocity * dt;
	}

	renderer_->UpdateParticles(particles_);

	remaining_duration_ -= dt;
	if(remaining_duration_ < 0)
	{
		Finish();
	}
}

void ParticleSystem::Finish()
{
	playing_ = false;
	if(settings_.destroy_on_finish)
	{
		entity_->Destroy();
	}
}

