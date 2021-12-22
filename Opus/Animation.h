#pragma once
#include "Component.h"
class Animation :
    public Component
{
public:
	Animation(const int frames, const float frame_time) : frames_(frames), frame_time_(frame_time)
	{
	}

	void Play();
	void Stop();
	void Reset();

	void Start() override;
	void Update() override;
private:
	void SetFrame();

	const int frames_;
	const float frame_time_;

	bool playing_ = true;

	int frame_width_ = 0;
	int frame_height_ = 0;
	
	int current_frame_ = 0;
	float current_frame_time_ = 0;
};
