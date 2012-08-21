#ifndef VIK_PLAYERFACTORY_HPP_INCLUDED
#define VIK_PLAYERFACTORY_HPP_INCLUDED

#include "viking/GameObjectFactory.hpp"
#include "viking/PlayerFactoryCreationParams.hpp"
#include "viking/PlayerFactoryConfiguration.hpp"

namespace vik
{

class EventSource;
class AnimationEngine;

// Creates actor decorated to be players
class PlayerFactory : public GameObjectFactory
{
public:
	PlayerFactory(const PlayerFactoryCreationParams& params, const PlayerFactoryConfiguration& defaultConfiguration);

	void setConfiguration(const PlayerFactoryConfiguration& config);
	const PlayerFactoryConfiguration& getConfiguration() const;
	std::shared_ptr<GameObject> create() override;
private:
	EventSource* playerEventSource;
	AnimationEngine& animationEngine;
	PlayerFactoryConfiguration configuration;
};

} // end namespace vik

#endif // VIK_PLAYERFACTORY_HPP_INCLUDED
