#include "viking/PlayerFactory.hpp"
#include "viking/Actor.hpp"
#include "viking/EventSource.hpp"
#include "viking/ControlScheme.hpp"
#include "viking/AnimationEngine.hpp"
#include "viking/GameApp.hpp"

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
	std::shared_ptr<Actor> player = std::make_shared<Actor>();

	playerEventSource->addListener(player);

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
	player->setSprite(spr);
	animationEngine.addSprite(spr);

	PlayerIdleState* idleState = new PlayerIdleState(player, ControlScheme());
	PlayerMobileState* mobileState = new PlayerMobileState(player, ControlScheme());

	player->addState(HashedString("Idle"), idleState);
	player->addState(HashedString("Mobile"), mobileState);

	player->startStateMachine(HashedString("Idle"));

	return player;
}

} // end namespace vik
