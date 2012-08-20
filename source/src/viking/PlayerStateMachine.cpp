#include "viking/PlayerStateMachine.hpp"
#include <cassert>

namespace vik
{

PlayerStateMachine::PlayerStateMachine(const std::weak_ptr<Actor>& context, const ControlScheme& controlScheme):
ActorStateMachine(context),
controlScheme(controlScheme),
idleState(context, this->controlScheme),
mobileState(context, this->controlScheme),
currentState(0)
{
}

void PlayerStateMachine::onStart()
{
	assert(!currentState);

	currentState = &idleState;
	currentState->onEnter();
}

void PlayerStateMachine::onStop()
{
	assert(currentState);

	currentState->onLeave();
	currentState = 0;
}

void PlayerStateMachine::onUpdate(GameTime& time)
{
	currentState->onUpdate(time);
}

void PlayerStateMachine::switchToState(const HashedString& stateName)
{
	assert(currentState);

	currentState->onLeave();

	if (stateName == HashedString("idle"))
	{
		currentState = &idleState;
	}
	else if (stateName == HashedString("mobile"))
	{
		currentState = &mobileState;
	}
	else
	{
		assert(false);
	}

	currentState->onEnter();
}

bool PlayerStateMachine::onEvent(const Event& e)
{
	return currentState ? currentState->onEvent(e) : false;
}

} // end namespace vik
