#include "viking/PlayerMobileState.hpp"

namespace vik
{

PlayerMobileState::PlayerMobileState(HashedString stateName, const std::weak_ptr<Actor>& context):
ActorState(stateName, context)
{
}

void PlayerMobileState::onEnter()
{
	//GameApp::getLogger()->log("void PlayerMobileState::onEnter()");
}

void PlayerMobileState::onUpdate(GameTime& time)
{
	//GameApp::getLogger()->log("void PlayerMobileState::onUpdate()");
}

void PlayerMobileState::onLeave()
{
	//GameApp::getLogger()->log("void PlayerMobileState::onLeave()");
}

bool PlayerMobileState::onEvent(const Event& e)
{
	return false;
}

} // end namespace vik
