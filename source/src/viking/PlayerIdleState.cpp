#include "viking/PlayerIdleState.hpp"
#include "viking/GameApp.hpp"
#include "viking/Event.hpp"
#include "viking/IrrlichtEvent.hpp"
#include "viking/ActorStateMachine.hpp"
#include <iostream>

namespace vik
{

PlayerIdleState::PlayerIdleState(const std::weak_ptr<Actor>& context, ControlScheme& scheme):
ActorState(context),
scheme(scheme)
{
}

void PlayerIdleState::onEnter()
{
	// GameApp::getSingleton().getLogger()->log("void PlayerIdleState::onEnter()");
	getContext().lock()->getParticle().setVelocity(irr::core::vector3df());
	auto spr = getContext().lock()->getSprite();
	spr->setLooping(true);
	spr->play(HashedString("idle"));
}

void PlayerIdleState::onUpdate(GameTime& time)
{
	// GameApp::getSingleton().getLogger()->log("void PlayerIdleState::onUpdate()");
}

void PlayerIdleState::onLeave()
{
	// GameApp::getSingleton().getLogger()->log("void PlayerIdleState::onLeave()");
}

bool PlayerIdleState::onEvent(const Event& e)
{
	if (e.getType() == HashedString("IrrlichtEvent"))
	{
		const irr::SEvent& se = static_cast<const IrrlichtEvent&>(e).getEvent();

		if (se.EventType == irr::EET_KEY_INPUT_EVENT)
		{
			if (se.KeyInput.PressedDown)
			{
				if (scheme.isDirectionalKey(se.KeyInput.Key))
				{
					getContext().lock()->getStateMachine()->switchToState(HashedString("mobile"));
					return true;
				}
				else if (scheme.getActionKeyIndex(se.KeyInput.Key) == 0)
				{
					getContext().lock()->getStateMachine()->switchToState(HashedString("attacking"));
					return true;
				}
			}
		}
	}

	return false;
}

} // end namespace vik
