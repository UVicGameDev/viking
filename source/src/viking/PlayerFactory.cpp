#include "viking/PlayerFactory.hpp"
#include "viking/Actor.hpp"
#include "viking/EventSource.hpp"
#include "viking/ControlScheme.hpp"
#include "viking/AnimationEngine.hpp"
#include "viking/GameApp.hpp"
#include "viking/PlayerStateMachine.hpp"

#include "viking/PlayerIdleState.hpp"
#include "viking/PlayerMobileState.hpp"

#include <cassert>

namespace vik
{

PlayerFactory::PlayerFactory(const PlayerFactoryCreationParams& params):
ActorFactory(params.factoryID),
playerEventSource(params.playerEventSource),
animationEngine(params.animationEngine),
configuration("",ControlScheme())
{
}

void PlayerFactory::setConfiguration(const PlayerFactoryConfiguration& config)
{
	configuration = config;
}

const PlayerFactoryConfiguration& PlayerFactory::getConfiguration() const
{
	return configuration;
}

std::shared_ptr<Actor> PlayerFactory::create()
{
	irr::scene::ISceneManager* smgr = GameApp::getSingleton().getSceneManager();

	std::string animDataPath = "../../../art/"
	+ configuration.playerType
	+ ".xml";

	auto sprData = animationEngine.load(animDataPath.c_str());

	assert(sprData);

	auto spr = std::make_shared<AnimatedSprite>(sprData, smgr->getRootSceneNode(), smgr);
	spr->setAnchor(ESA_FEET);
	animationEngine.addSprite(spr);

	auto player = std::make_shared<Actor>();

	// std::shared_ptr<PlayerStateMachine> stateMachine = std::shared_ptr<PlayerStateMachine>(new PlayerStateMachine(player, HashedString("idle"), configuration.controlScheme));
	auto stateMachine = std::make_shared<PlayerStateMachine>(player, HashedString("idle"), configuration.controlScheme);
	stateMachine->initStates();
	player->setStateMachine(stateMachine);
	player->setSprite(spr);
	playerEventSource->addListener(player);

	player->start();

	return player;
}

} // end namespace vik
