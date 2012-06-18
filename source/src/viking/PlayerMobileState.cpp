#include "viking/PlayerMobileState.hpp"
#include "viking/PlayerMovementAnimator.hpp"
#include "viking/GameApp.hpp"

namespace vik
{

PlayerMobileState::PlayerMobileState(HashedString stateName, const std::weak_ptr<Actor>& context, const ControlScheme& scheme):
ActorState(stateName, context),
movementAnimator(*context.lock(), scheme)
{
}

void PlayerMobileState::onEnter()
{
	GameApp::getLogger()->log("void PlayerMobileState::onEnter()");
}

void PlayerMobileState::onUpdate(GameTime& time)
{
	GameApp::getLogger()->log("void PlayerMobileState::onUpdate()");

	movementAnimator.update(time);

	// TODO: Consider that may stop moving because of other external cause such as being hurt
	// Probably not a bad idea to handle through onEvent?
	// In fact, maybe doneMoving should be handled through an event...
	if (movementAnimator.doneMoving())
	{
		movementAnimator.reset();
		getContext().lock()->switchToState(HashedString("Idle"));
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
