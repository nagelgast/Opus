#include "Collision.h"

#include "Entity.h"
#include "Vector2.h"

Collision::Collision(Entity* const e, const Vector2* const v): hit(true), other(e), displacement(v)
{
}
