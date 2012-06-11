#ifndef PLAYERFACTORY_HPP_INCLUDED
#define PLAYERFACTORY_HPP_INCLUDED

#include "viking/GameObjectFactory.hpp"

namespace vik
{

class EventSource;

// Creates actor decorated to be players
class PlayerFactory : public GameObjectFactory
{
public:
	PlayerFactory(HashedString factoryID, EventSource* playerEventSource);
	std::shared_ptr<GameObject> create();
private:
	EventSource* playerEventSource;
};

} // end namespace vik

#endif // PLAYERFACTORY_HPP_INCLUDED
