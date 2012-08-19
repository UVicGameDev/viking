#ifndef PLAYERFACTORY_HPP_INCLUDED
#define PLAYERFACTORY_HPP_INCLUDED

#include "viking/GameObjectFactory.hpp"

namespace vik
{

class EventSource;
class AnimationEngine;

// Creates actor decorated to be players
class PlayerFactory : public GameObjectFactory
{
public:
	PlayerFactory(HashedString factoryID, EventSource* playerEventSource, AnimationEngine& animationEngine);
	std::shared_ptr<GameObject> create();
private:
	EventSource* playerEventSource;
	AnimationEngine& animationEngine;
};

} // end namespace vik

#endif // PLAYERFACTORY_HPP_INCLUDED
