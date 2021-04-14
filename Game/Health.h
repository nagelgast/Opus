#pragma once
#include "../Opus/Component.h"

class Health :
    public Component
{
public:
    Health(int max_health);

    void Start() override;

    void TakeDamage(int amount);

    int GetHealth() const;
    int GetMaxHealth() const;
private:
    void Die();

    int current_health_;
    int max_health_;
};

