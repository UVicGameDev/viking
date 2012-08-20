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
GameObjectFactory(params.factoryID),
playerEventSource(params.playerEventSource),
animationEngine(params.animationEngine),
playerType(params.playerType)
{
}

std::shared_ptr<GameObject> PlayerFactory::create()
{
	irr::scene::ISceneManager* smgr = GameApp::getSingleton().getSceneManager();

	std::string animdatapath = "../../../art/";

	if (playerType == EPT_ARTSIE)
	{
		animdatapath += "artsie.xml";
	}
	else
	{
		assert(false);
	}

	auto sprData = animationEngine.load(animdatapath.c_str());

	assert(sprData);

	auto spr = std::make_shared<AnimatedSprite>(sprData, smgr->getRootSceneNode(), smgr);
	spr->setAnchor(ESA_FEET);
	animationEngine.addSprite(spr);

	std::shared_ptr<Actor> player = std::make_shared<Actor>();

	ControlScheme controlScheme(irr::KEY_UP, irr::KEY_DOWN, irr::KEY_LEFT, irr::KEY_RIGHT);

	PlayerStateMachine* stateMachine = new PlayerStateMachine(player, controlScheme);
	player->setStateMachine(stateMachine);
	player->setSprite(spr);
	playerEventSource->addListener(player);

	player->start();

	return player;
}

} // end namespace vik
