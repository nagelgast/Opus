#include "SFMLTime.h"

SFMLTime::SFMLTime(const int fixed_time_step) :
fixed_time_step_(sf::milliseconds(fixed_time_step)), clock_(), elapsed_time_(), delta_time_(), update_delay_(), fixed_time_step_ticks_()
{
}

float SFMLTime::GetDeltaTime() const
{
    return delta_time_.asSeconds();
}

float SFMLTime::GetTimeSinceStartup() const
{
    return elapsed_time_.asSeconds();
}

int SFMLTime::GetFixedTimeStepTicks() const
{
    return 0.0f;
}

void SFMLTime::Tick()
{
	const auto current_time = clock_.getElapsedTime();
	delta_time_ = current_time - elapsed_time_;
	elapsed_time_ = current_time;
	update_delay_ += delta_time_;

	fixed_time_step_ticks_ = 0;
	while (update_delay_ > fixed_time_step_)
	{
		fixed_time_step_ticks_++;
		update_delay_ -= fixed_time_step_;
	}
}
