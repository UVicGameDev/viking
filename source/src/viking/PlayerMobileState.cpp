#include "viking/PlayerMobileState.hpp"
#include "viking/GameApp.hpp"

namespace vik
{

PlayerMobileState::PlayerMobileState(const std::weak_ptr<Actor>& context, const ControlScheme& scheme):
ActorState(context),
scheme(scheme)
{
}

void PlayerMobileState::onEnter()
{
	GameApp::getLogger()->log("void PlayerMobileState::onEnter()");
}

void PlayerMobileState::onUpdate(GameTime& time)
{
	// GameApp::getLogger()->log("void PlayerMobileState::onUpdate()");

	const irr::core::vector3df movementModifier(100.0f, 100.0f, 100.0f);
	const KeyMap& k = GameApp::getKeyMap();
	irr::core::vector3df currVel;

	if (k.isKeyDown(scheme.up))
	{
		currVel.Y -= movementModifier.Y;
	}
	if (k.isKeyDown(scheme.down))
	{
		currVel.Y += movementModifier.Y;
	}
	if (k.isKeyDown(scheme.left))
	{
		currVel.X -= movementModifier.X;
	}
	if (k.isKeyDown(scheme.right))
	{
		currVel.X += movementModifier.X;
	}

	// if velocity is 0, set flag that movement is done.
	if (currVel == irr::core::vector3df())
	{
		getContext().lock()->switchToState(HashedString("Idle"));
	}
	else
	{
		getContext().lock()->getParticle().setVelocity( currVel );
	}
}

void PlayerMobileState::onLeave()
{
	GameApp::getLogger()->log("void PlayerMobileState::onLeave()");
	getContext().lock()->getParticle().setVelocity(irr::core::vector3df());
}

bool PlayerMobileState::onEvent(const Event& e)
{
	return false;
}

} // end namespace vik
