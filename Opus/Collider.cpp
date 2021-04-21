#include "pch.h"
#include "Collider.h"


Collider::Collider(int layer, Shape shape, bool fixed) : layer_(layer), shape_(shape), fixed_(fixed)
{
}

void Collider::OnCollision()
{
}
