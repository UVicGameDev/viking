#include "viking/Actor.hpp"
#include "viking/GameTime.hpp"
#include "viking/ActorStateMachine.hpp"
#include "viking/ActorState.hpp"
#include "viking/GameApp.hpp"
#include <cassert>
#include <iostream>

namespace vik
{

Actor::Actor():
stateMachine(0),
running(false)
{
}

void Actor::setStateMachine(const std::shared_ptr<ActorStateMachine>& stateMachine)
{
	this->stateMachine = stateMachine;
	stateMachine->addListener(shared_from_this());
}

std::shared_ptr<ActorStateMachine>& Actor::getStateMachine()
{
	return stateMachine;
}

void Actor::start()
{
	assert(!running);

	running = true;

	if (stateMachine)
	{
		stateMachine->start();
	}
}

void Actor::stop()
{
	assert(running);

	running = false;

	if (stateMachine)
	{
		stateMachine->stop();
	}
}

void Actor::update(GameTime& time)
{
	if (!running) return;

	if (stateMachine)
	{
		stateMachine->update(time);
	}

	particle.update(time);

	if (sprite)
	{
		sprite->setPosition(particle.getPosition());
	}
}

bool Actor::isRunning() const
{
	return running;
}

bool Actor::onEvent(const Event& e)
{
	// check if upstream event
	bool isUpstream = false;
	if (stateMachine && e.getSender() == stateMachine)
	{
		isUpstream = true;
	}

	if (isUpstream)
	{
		return distributeEvent(e);
	}
	else
	{
		return stateMachine ? stateMachine->onEvent(e) : false;
	}
}

Particle& Actor::getParticle()
{
	return particle;
}

void Actor::setSprite(std::shared_ptr<AnimatedSprite>& sprite)
{
	this->sprite = sprite;
}

std::shared_ptr<AnimatedSprite>& Actor::getSprite()
{
	return sprite;
}

const std::shared_ptr<AnimatedSprite>& Actor::getSprite() const
{
	return sprite;
}

void Actor::serializeAttributes(irr::io::IAttributes* out, irr::io::SAttributeReadWriteOptions* options) const
{
	// TODO: Figure out serialization of other properties
	out->addBool("running", running);
}

void Actor::deserializeAttributes(irr::io::IAttributes* in, irr::io::SAttributeReadWriteOptions* options)
{
	// TODO: Figure out serialization of other properties
	running = in->getAttributeAsBool("running");
}

} // end namespace vik
