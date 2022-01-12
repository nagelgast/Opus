#pragma once
#include "Sprite.h"

struct ParticleSettings
{
    Sprite sprite;
    int size;
    bool auto_play = true;
    bool destroy_on_finish = true;
    bool looping = false;

    float duration = 1;
    float lifetime = 1;
    int particle_count = 1;
};
