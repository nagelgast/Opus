#pragma once
#include "Color.h"
#include "Sprite.h"

struct ParticleSettings
{
    Sprite sprite;
    Color color;

    int size;
    int particle_count = 1;
    float speed = 0;
    float duration = 1;
    float lifetime = 1;

    bool auto_play = true;
    bool destroy_on_finish = true;
    bool looping = false;
};
