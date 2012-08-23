#include "viking/PlayerStateMachine.hpp"
#include <cassert>

namespace vik
{

PlayerStateMachine::PlayerStateMachine(const std::weak_ptr<Actor>& context, const HashedString& initialState, const ControlScheme& controlScheme):
ActorStateMachine(context, initialState),
controlScheme(controlScheme)
{
}

void PlayerStateMachine::initStates()
{
	addState(HashedString("idle"),
			std::make_shared<PlayerIdleState>(getContext(), controlScheme));
	addState(HashedString("mobile"),
			std::make_shared<PlayerMobileState>(getContext(), controlScheme));
	addState(HashedString("attacking"),
			std::make_shared<PlayerAttackingState>(getContext(), controlScheme));
}

} // end namespace vik
