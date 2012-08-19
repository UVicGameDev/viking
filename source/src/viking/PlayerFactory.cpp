#include "viking/PlayerFactory.hpp"
#include "viking/Actor.hpp"
#include "viking/EventSource.hpp"
#include "viking/ControlScheme.hpp"
#include "viking/AnimationEngine.hpp"
#include "viking/GameApp.hpp"

#include "viking/PlayerIdleState.hpp"
#include "viking/PlayerMobileState.hpp"

#include <iostream>

namespace vik
{

PlayerFactory::PlayerFactory(HashedString factoryID, EventSource* playerEventSource, AnimationEngine& animationEngine):
GameObjectFactory(factoryID),
playerEventSource(playerEventSource),
animationEngine(animationEngine)
{
}

static int nodeTreeSize(irr::scene::ISceneNode* node)
{
	int numChildren = 1;
	for (auto it = node->getChildren().begin(); it != node->getChildren().end(); ++it)
	{
		numChildren += nodeTreeSize(*it);
	}
	return numChildren;
}

std::shared_ptr<GameObject> PlayerFactory::create()
{
	std::shared_ptr<Actor> player = std::make_shared<Actor>();

	playerEventSource->addListener(player);

	PlayerIdleState* idleState = new PlayerIdleState(player, ControlScheme());
	PlayerMobileState* mobileState = new PlayerMobileState(player, ControlScheme());

	player->addState(hashString("Idle"), idleState);
	player->addState(hashString("Mobile"), mobileState);

	player->startStateMachine(hashString("Idle"));

	irr::scene::ISceneManager* smgr = GameApp::getSingleton().getSceneManager();

	// std::cout << "Before creating sprite: " << nodeTreeSize(smgr->getRootSceneNode()) << std::endl;;

	auto sprData = animationEngine.load("../../../art/player.xml");
	auto spr = std::make_shared<AnimatedSprite>(sprData, smgr->getRootSceneNode(), smgr);
	spr->setAnchor(ESA_FEET);
	animationEngine.addSprite(spr);
	player->setSprite(spr);
	player->getSprite()->play(hashString("walk"));

	// std::cout << "After creating sprite: " << nodeTreeSize(smgr->getRootSceneNode()) << std::endl;;

	return player;
}

} // end namespace vik
