#ifndef VIK_PLAYERFACTORY_HPP_INCLUDED
#define VIK_PLAYERFACTORY_HPP_INCLUDED

#include "viking/GameObjectFactory.hpp"
#include "viking/PlayerFactoryCreationParams.hpp"

namespace vik
{

class EventSource;
class AnimationEngine;

// Creates actor decorated to be players
class PlayerFactory : public GameObjectFactory
{
public:
	PlayerFactory(const PlayerFactoryCreationParams& params);
	std::shared_ptr<GameObject> create();
private:
	EventSource* playerEventSource;
	AnimationEngine& animationEngine;
	ePlayerType playerType;
};

} // end namespace vik

#endif // VIK_PLAYERFACTORY_HPP_INCLUDED
