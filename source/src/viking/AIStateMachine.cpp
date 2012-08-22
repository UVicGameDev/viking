#include "viking/AIStateMachine.hpp"
#include <cassert>

namespace vik
{

AIStateMachine::AIStateMachine(const std::weak_ptr<Actor>& context):
ActorStateMachine(context),
idleState(context),
currentState(0)
{
}

void AIStateMachine::onStart()
{
	assert(!currentState);

	currentState = &idleState;
	currentState->onEnter();
}

void AIStateMachine::onStop()
{
	assert(currentState);

	currentState->onLeave();
	currentState = 0;
}

void AIStateMachine::onUpdate(GameTime& time)
{
	currentState->onUpdate(time);
}

void AIStateMachine::switchToState(const HashedString& stateName)
{
	assert(currentState);

	currentState->onLeave();
	
	// TODO: handle state change

	currentState->onEnter();
}

bool AIStateMachine::onEvent(const Event& e)
{
	return currentState ? currentState->onEvent(e) : false;
}

} // end namespace vik
