#ifndef VIK_PARTICLE_HPP_INCLUDED
#define VIK_PARTICLE_HPP_INCLUDED

#include <irrlicht/vector3d.h>
#include "viking/GameTime.hpp"

namespace vik
{

// Contains information for position, velocity, acceleration in continuous space.
// units are in px / second
class Particle
{
public:
	const irr::core::vector3df& getPosition() const { return position; }
	const irr::core::vector3df& getVelocity() const { return velocity; }
	const irr::core::vector3df& getAcceleration() const { return acceleration; }

	void setPosition(const irr::core::vector3df& p){ position = p; }
	void setVelocity(const irr::core::vector3df& v){ velocity = v; }
	void setAcceleration(const irr::core::vector3df& a){ acceleration = a; }

	// updates position and velocity.
	void update(GameTime& time);
private:
	irr::core::vector3df position;
	irr::core::vector3df velocity;
	irr::core::vector3df acceleration;
};

} // end namespace vik

#endif // VIK_PARTICLE_HPP_INCLUDED
