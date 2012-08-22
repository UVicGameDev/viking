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

	irr::core::vector3df movementDirection;
	const float velocityMagnitude = 225.f;
	const std::shared_ptr<KeyMap>& k = GameApp::getSingleton().getKeyMap();
	irr::core::vector3df currVel;

	if (k->isKeyDown(scheme.upKey) != k->isKeyDown(scheme.downKey))
	{
		if (k->isKeyDown(scheme.upKey))
		{
			movementDirection.Y -= 1.0f;
		}
		if (k->isKeyDown(scheme.downKey))
		{
			movementDirection.Y += 1.0f;
		}
	}

	if (k->isKeyDown(scheme.leftKey) != k->isKeyDown(scheme.rightKey))
	{
		if (k->isKeyDown(scheme.leftKey))
		{
			movementDirection.X -= 1.0f;
			getContext().lock()->getSprite()->setFlipHorizontal(true);
		}
		if (k->isKeyDown(scheme.rightKey))
		{
			movementDirection.X += 1.0f;
			getContext().lock()->getSprite()->setFlipHorizontal(false);
		}
	}

	// if velocity is 0, set flag that movement is done.
	if (movementDirection == irr::core::vector3df())
	{
		getContext().lock()->getStateMachine()->switchToState(HashedString("idle"));
	}
	else
	{
		movementDirection.normalize();
		movementDirection *= velocityMagnitude;
		getContext().lock()->getParticle().setVelocity(movementDirection);
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
