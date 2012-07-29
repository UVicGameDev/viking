#include "viking/Actor.hpp"
#include "viking/GameTime.hpp"
#include "viking/ActorState.hpp"
#include "viking/GameApp.hpp"
#include <cassert>
#include <iostream>

namespace vik
{

Actor::Actor():
currentState(0),
sprite(0)
{
}

Actor::~Actor()
{
	if (currentState)
	{
		currentState->onLeave();
	}

	for (int i = static_cast<int>(states.size()) - 1; i >= 0; --i)
	{
		delete states[i].second;
	}
}

void Actor::startStateMachine(HashedString initialStateName)
{
	unsigned i;
	for (i = 0; i < states.size(); ++i)
	{
		if (states[i].first == initialStateName)
		{
			currentState = states[i].second;
			break;
		}
	}
	assert(i != states.size());

	currentState->onEnter();
}

void Actor::addState(HashedString stateName, ActorState* state)
{
	states.push_back(std::pair<HashedString,ActorState*>(stateName,state));
}

void Actor::switchToState(HashedString nextState)
{
	currentState->onLeave();

	unsigned i;
	for (i = 0; i < states.size(); ++i)
	{
		if (states[i].first == nextState)
		{
			currentState = states[i].second;
			break;
		}
	}
	assert(i != states.size());

	currentState->onEnter();
}

void Actor::update(GameTime& time)
{
	// std::cout << "Actor::update()" << std::endl;

	currentState->onUpdate(time);

	particle.update(time);

	sprite.setPosition(particle.getPosition());
}

bool Actor::onEvent(const Event& e)
{
	return currentState->onEvent(e);
}

Particle& Actor::getParticle()
{
	return particle;
}

} // end namespace vik
