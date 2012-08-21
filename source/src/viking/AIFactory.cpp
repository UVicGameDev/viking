#include "viking/AIFactory.hpp"
#include "viking/EventSource.hpp"
#include "viking/AnimationEngine.hpp"

namespace vik
{

AIFactory::AIFactory(HashedString factoryID, EventSource* aiEventSource, AnimationEngine& animationEngine):
GameObjectFactory(factoryID),
aiEventSource(aiEventSource),
animationEngine(animationEngine)
{
}

std::shared_ptr<GameObject> AIFactory::create()
{
	/*
	std::shared_ptr<Actor> ai = std::make_shared<Actor>();

	AIStateMachine* stateMachine = new AIStateMachine(ai);
	ai->setStateMachine(stateMachine);
	*/

	return std::shared_ptr<GameObject>();
}

} // end namespace vik
