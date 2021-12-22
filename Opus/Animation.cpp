#include "pch.h"
#include "Animation.h"

#include "BaseEntityRenderer.h"
#include "SpriteRenderer.h"

void Animation::Play()
{
	playing_ = true;
}

void Animation::Stop()
{
	playing_ = false;
	current_frame_time_ = 0;
}

void Animation::Reset()
{
	Stop();
	current_frame_ = 0;
	SetFrame();
}

void Animation::Start()
{
	const auto rect = entity_->GetRenderer()->GetTextureRect();
	frame_width_ = static_cast<int>(rect.width);
	frame_height_ = static_cast<int>(rect.height);
}

void Animation::Update()
{
	if(!playing_) return;

	const auto dt = entity_->GetDeltaTime();
	current_frame_time_ += dt;
	if(current_frame_time_ > frame_time_)
	{
		current_frame_time_ -= frame_time_;
		current_frame_++;
		if(current_frame_ == frames_)
		{
			current_frame_ = 0;
		}

		SetFrame();
	}
}

void Animation::SetFrame()
{
	entity_->GetRenderer()->SetTextureRect({ 0, current_frame_ * frame_width_, frame_width_, frame_height_ });
}