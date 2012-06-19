#ifndef PLAYER_MOVEMENT_ANIMATOR_HPP
#define PLAYER_MOVEMENT_ANIMATOR_HPP

#include "viking/ActorAnimator.hpp"
#include "viking/EventListener.hpp"
#include "viking/ControlScheme.hpp"
#include <irrlicht/vector3d.h>

namespace vik
{

class Event;

// automatically makes player move and animate based on keyboard input
class PlayerMovementAnimator : public ActorAnimator
{
public:
	PlayerMovementAnimator(Actor& target, const ControlScheme& scheme):
	ActorAnimator(target),
	scheme(scheme)
	{
		reset();
	}

	// resets state of animator. to be called when it stops being used.
	void reset();

	void update(GameTime& time);

	// true if stopped moving, false otherwise
	// used to know if state change must be triggered from the outside
	bool doneMoving() const;

	// px per second
	void setMovementSpeed(float speed);
	float getMovementSpeed() const;
private:
	ControlScheme scheme;
	bool doneMovingFlag;

	// the speed of the particle is set to this vector
	irr::core::vector3df movementModifier;
};

} // end namespace vik

#endif // PLAYER_MOVEMENT_ANIMATOR_HPP
