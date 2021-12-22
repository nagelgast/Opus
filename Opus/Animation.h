#pragma once
#include "Component.h"
class Animation :
    public Component
{
public:
	Animation(const int frames, const float frame_time) : frames_(frames), frame_time_(frame_time)
	{
	}

	void Start() override;
	void Update() override;
private:
	const int frames_;
	const float frame_time_;

	int frame_width_ = 0;
	int frame_height_ = 0;
	
	int current_frame_ = 0;
	float current_frame_time_ = 0;
};
