#include "viking/ActorStateMachine.hpp"
#include "viking/ActorState.hpp"
#include <cassert>

namespace vik
{

ActorStateMachine::ActorStateMachine(const std::weak_ptr<Actor>& context, const HashedString& initialState):
context(context),
running(false),
initialState(initialState),
currentState(0)
{
}

ActorStateMachine::~ActorStateMachine()
{
	if (running)
	{
		stop();
	}
}

void ActorStateMachine::start()
{
	assert(!running);
	assert(!currentState);
	assert(states.find(initialState) != states.end());

	running = true;
	currentState = states[initialState];
	currentState->onEnter();

	onStart();
}

void ActorStateMachine::update(GameTime& time)
{
	if (running)
	{
		onPreUpdate(time);
		currentState->onUpdate(time);
		onPostUpdate(time);
	}
}

void ActorStateMachine::stop()
{
	assert(running);
	assert(currentState);

	onStop();

	running = false;
	currentState->onLeave();
	currentState = 0;
}

bool ActorStateMachine::isRunning() const
{
	return running;
}

bool ActorStateMachine::onEvent(const Event& e)
{
	// forward event upstream if it is going upstream
	if (currentState && e.getSender() == currentState)
	{
		// give specific implementation a chance to handle it.
		if (onPreUpstreamEvent(e))
		{
			return true;
		}
		else
		{
			return distributeEvent(e);
		}
	}
	// otherwise forward downstream
	else if (currentState)
	{
		// give specific implementation a chance to handle it.
		if (onPreDownstreamEvent(e))
		{
			return true;
		}
		else
		{
			return currentState->onEvent(e);
		}
	}
	// not handled because no current state
	else
	{
		return false;
	}
}

void ActorStateMachine::addState(const HashedString& stateName, const std::shared_ptr<ActorState>& state)
{
	assert(state);
	assert(states.find(stateName) == states.end());

	states[stateName] = state;

	state->addListener(shared_from_this());
}

void ActorStateMachine::switchToState(const HashedString& stateName)
{
	assert(currentState);
	assert(states.find(stateName) != states.end());

	currentState->onLeave();

	currentState = states.find(stateName)->second;

	currentState->onEnter();
}

std::shared_ptr<ActorState>& ActorStateMachine::getCurrentState()
{
	return currentState;
}

std::weak_ptr<Actor>& ActorStateMachine::getContext()
{
	return context;
}

const std::weak_ptr<Actor>& ActorStateMachine::getContext() const
{
	return context;
}

void ActorStateMachine::serializeAttributes(irr::io::IAttributes* out, irr::io::SAttributeReadWriteOptions* options) const
{
	// TODO: Handle saving reference to context
	out->addBool("running", running);
}

void ActorStateMachine::deserializeAttributes(irr::io::IAttributes* in, irr::io::SAttributeReadWriteOptions* options)
{
	// TODO: Handle saving reference to context
	running = in->getAttributeAsBool("running");
}

} // end namespace vik
