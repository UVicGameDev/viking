#include "viking/PlayerIdleState.hpp"
#include "viking/GameApp.hpp"
#include "viking/Event.hpp"
#include "viking/IrrlichtEvent.hpp"
#include <iostream>

namespace vik
{

PlayerIdleState::PlayerIdleState(const std::weak_ptr<Actor>& context, const ControlScheme& scheme):
ActorState(context),
scheme(scheme)
{
}

void PlayerIdleState::onEnter()
{
	GameApp::getSingleton().getLogger()->log("void PlayerIdleState::onEnter()");
}

void PlayerIdleState::onUpdate(GameTime& time)
{
	// GameApp::getSingleton().getLogger()->log("void PlayerIdleState::onUpdate()");
}

void PlayerIdleState::onLeave()
{
	GameApp::getSingleton().getLogger()->log("void PlayerIdleState::onLeave()");
}

bool PlayerIdleState::onEvent(const Event& e)
{
	if (e.getType() == hashString("IrrlichtEvent"))
	{
		const irr::SEvent& se = static_cast<const IrrlichtEvent&>(e).getEvent();

		if (se.EventType == irr::EET_KEY_INPUT_EVENT)
		{
			if (scheme.isDirectionalKey(se.KeyInput.Key) && se.KeyInput.PressedDown)
			{
				getContext().lock()->switchToState(hashString("Mobile"));
				return true;
			}
		}
	}

	return false;
}

} // end namespace vik
