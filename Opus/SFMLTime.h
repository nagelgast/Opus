#pragma once

#include "BaseTime.h"
#include <SFML/System/Clock.hpp>

class SFMLTime final:
    public BaseTime
{
public:
	explicit SFMLTime(int fixed_time_step);

    float GetDeltaTime() const override;
    float GetTimeSinceStartup() const override;
    int GetFixedTimeStepTicks() const override;
    void Tick() override;

private:
    const sf::Time fixed_time_step_;
    const sf::Clock clock_;
    sf::Time elapsed_time_;
    sf::Time delta_time_;
    sf::Time update_delay_;
    int fixed_time_step_ticks_;
};

