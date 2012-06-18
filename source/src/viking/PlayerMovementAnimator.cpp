#include "viking/PlayerMovementAnimator.hpp"
#include "viking/GameApp.hpp"
#include "viking/Actor.hpp"
#include <irrlicht/vector3d.h>
#include <iostream>

namespace vik
{

void PlayerMovementAnimator::reset()
{
	doneMovingFlag = false;
	movementModifier.set(50.0f, 50.0f, 50.0f);
}

void PlayerMovementAnimator::update(GameTime& time)
{
	const KeyMap& k = GameApp::getKeyMap();
	irr::core::vector3df currVel;

	if (k.isKeyDown(scheme.up))
	{
		currVel.Y += movementModifier.Y;
		std::cout << "Y" << currVel.Y << std::endl;
	}
	if (k.isKeyDown(scheme.down))
	{
		currVel.Y -= movementModifier.Y;
		std::cout << "Y" << currVel.Y << std::endl;
	}
	if (k.isKeyDown(scheme.left))
	{
		currVel.X -= movementModifier.X;
		std::cout << "X" << currVel.X << std::endl;
	}
	if (k.isKeyDown(scheme.right))
	{
		currVel.X += movementModifier.X;
		std::cout << "X" << currVel.X << std::endl;
	}

	// if velocity is 0, set flag that movement is done.
	if (currVel == irr::core::vector3df())
	{
		doneMovingFlag = true;
	}
	else
	{
		target.getParticle().setVelocity( currVel );
	}
}

bool PlayerMovementAnimator::doneMoving() const
{
	return doneMovingFlag;
}

} // end namespace vik
