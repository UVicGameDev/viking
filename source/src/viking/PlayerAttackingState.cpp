#include "viking/PlayerAttackingState.hpp"
#include "viking/ActorStateMachine.hpp"
#include "viking/KeyMap.hpp"
#include "viking/GameApp.hpp"

namespace vik
{

PlayerAttackingState::PlayerAttackingState(const std::weak_ptr<Actor>& context, ControlScheme& scheme):
ActorState(context),
scheme(scheme)
{
}

void PlayerAttackingState::onEnter()
{
	getContext().lock()->getParticle().setVelocity(irr::core::vector3df());
	auto spr = getContext().lock()->getSprite();
	spr->setLooping(false);
	spr->play(HashedString("attack"));
}

void PlayerAttackingState::onUpdate(GameTime& time)
{
	auto spr = getContext().lock()->getSprite();
	if (!spr->getPlaying())
	{
		const std::shared_ptr<KeyMap>& k = GameApp::getSingleton().getKeyMap();
		if (k->isKeyDown(scheme.upKey) ||
				k->isKeyDown(scheme.downKey) ||
				k->isKeyDown(scheme.leftKey) ||
				k->isKeyDown(scheme.rightKey))
		{
			getContext().lock()->getStateMachine()->switchToState(HashedString("mobile"));
		}
		else
		{
			getContext().lock()->getStateMachine()->switchToState(HashedString("idle"));
		}
	}
}

void PlayerAttackingState::onLeave()
{
}

bool PlayerAttackingState::onEvent(const Event& e)
{
	return false;
}

} // end namespace vik
