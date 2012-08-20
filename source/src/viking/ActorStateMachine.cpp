#include "viking/ActorStateMachine.hpp"
#include <cassert>

namespace vik
{

ActorStateMachine::ActorStateMachine(const std::weak_ptr<Actor>& context):
context(context),
running(false)
{
}

void ActorStateMachine::start()
{
	assert(!running);
	running = true;
	onStart();
}

void ActorStateMachine::update(GameTime& time)
{
	if (running)
	{
		onUpdate(time);
	}
}

void ActorStateMachine::stop()
{
	assert(running);
	running = false;
	onStop();
}

bool ActorStateMachine::isRunning() const
{
	return running;
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
