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
	//
	const std::shared_ptr<KeyMap>& k = GameApp::getSingleton().getKeyMap();

	// example: won't switch to mobile state if you're pressing both left and right at the same time.
	if ((k->isKeyDown(scheme.upKey) != k->isKeyDown(scheme.downKey) ||
		(k->isKeyDown(scheme.leftKey) != k->isKeyDown(scheme.rightKey))))
	{
		getContext().lock()->getStateMachine()->switchToState(HashedString("mobile"));
	}
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
				if (scheme.getActionKeyIndex(se.KeyInput.Key) == 0)
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
