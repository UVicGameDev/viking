#include "viking/PlayerMobileState.hpp"
#include "viking/GameApp.hpp"
#include "viking/ActorStateMachine.hpp"
#include "viking/IrrlichtEvent.hpp"

namespace vik
{

PlayerMobileState::PlayerMobileState(const std::weak_ptr<Actor>& context, ControlScheme& scheme):
ActorState(context),
scheme(scheme)
{
}

void PlayerMobileState::onEnter()
{
	// GameApp::getSingleton().getLogger()->log("void PlayerMobileState::onEnter()");
	auto spr = getContext().lock()->getSprite();
	spr->setLooping(true);
	spr->play(HashedString("mobile"));
}

void PlayerMobileState::onUpdate(GameTime& time)
{
	// GameApp::getSingleton().getLogger()->log("void PlayerMobileState::onUpdate()");

	const irr::core::vector3df movementModifier(100.0f, 100.0f, 100.0f);
	const KeyMap& k = GameApp::getSingleton().getKeyMap();
	irr::core::vector3df currVel;

	if (k.isKeyDown(scheme.upKey))
	{
		currVel.Y -= movementModifier.Y;
	}
	if (k.isKeyDown(scheme.downKey))
	{
		currVel.Y += movementModifier.Y;
	}
	if (k.isKeyDown(scheme.leftKey))
	{
		currVel.X -= movementModifier.X;
		getContext().lock()->getSprite()->setFlipHorizontal(true);
	}
	if (k.isKeyDown(scheme.rightKey))
	{
		currVel.X += movementModifier.X;
		getContext().lock()->getSprite()->setFlipHorizontal(false);
	}

	// if velocity is 0, set flag that movement is done.
	if (currVel == irr::core::vector3df())
	{
		getContext().lock()->getStateMachine()->switchToState(HashedString("idle"));
	}
	else
	{
		getContext().lock()->getParticle().setVelocity( currVel );
	}
}

void PlayerMobileState::onLeave()
{
	// GameApp::getSingleton().getLogger()->log("void PlayerMobileState::onLeave()");
	// getContext().lock()->getParticle().setVelocity(irr::core::vector3df());
}

bool PlayerMobileState::onEvent(const Event& e)
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
