#include "viking/AIFactory.hpp"
#include "viking/EventSource.hpp"
#include "viking/AnimationEngine.hpp"
#include "viking/AIStateMachine.hpp"
#include "viking/GameApp.hpp"
#include <cassert>

namespace vik
{

AIFactory::AIFactory(HashedString factoryID, EventSource* aiEventSource, AnimationEngine& animationEngine):
ActorFactory(factoryID),
aiEventSource(aiEventSource),
animationEngine(animationEngine)
{
}

std::shared_ptr<Actor> AIFactory::create()
{
	irr::scene::ISceneManager* smgr = GameApp::getSingleton().getSceneManager();

	std::string animDataPath = "../../../art/sandbag.xml";

	auto sprData = animationEngine.load(animDataPath.c_str());

	assert(sprData);

	auto spr = std::make_shared<AnimatedSprite>(sprData, smgr->getRootSceneNode(), smgr);
	spr->setAnchor(ESA_FEET);
	animationEngine.addSprite(spr);

	std::shared_ptr<Actor> ai = std::make_shared<Actor>();

	auto stateMachine = std::make_shared<AIStateMachine>(ai, HashedString("idle"));
	stateMachine->initStates();
	ai->setStateMachine(stateMachine);
	ai->setSprite(spr);
	aiEventSource->addListener(ai);

	ai->start();

	return ai;
}

} // end namespace vik
