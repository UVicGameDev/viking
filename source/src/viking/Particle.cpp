#include "viking/Particle.hpp"
#include <iostream>

namespace vik
{

void Particle::update(GameTime& time)
{
	float dt = time.getDeltaTimeSeconds();

	velocity += acceleration * dt;
	position += velocity * dt;
}

} // end namespace vik
