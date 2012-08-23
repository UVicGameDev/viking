#include "viking/AIStateMachine.hpp"
#include <cassert>

namespace vik
{

AIStateMachine::AIStateMachine(const std::weak_ptr<Actor>& context, const HashedString& initialState):
ActorStateMachine(context, initialState)
{
}

void AIStateMachine::initStates()
{
	addState(HashedString("idle"),
			std::make_shared<AIIdleState>(getContext()));
}

} // end namespace vik
