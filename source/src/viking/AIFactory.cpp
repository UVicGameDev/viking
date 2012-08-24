#include "viking/AIFactory.hpp"
#include "viking/EventSource.hpp"
#include "viking/AnimationEngine.hpp"
#include "viking/AIStateMachine.hpp"
#include "viking/GameApp.hpp"
#include "viking/Team.hpp"
#include <cassert>

namespace vik
{

AIFactory::AIFactory(HashedString factoryID, EventSource* aiEventSource, AnimationEngine& animationEngine):
ActorFactory(factoryID),
aiEventSource(aiEventSource),
animationEngine(animationEngine)
{
}

void AIFactory::setConfiguration(const std::string& aiName, Team* membershipSupplier)
{
	this->aiName = aiName;
	this->membershipSupplier = membershipSupplier;
}

std::shared_ptr<Actor> AIFactory::create()
{
	irr::scene::ISceneManager* smgr = GameApp::getSingleton().getSceneManager();

	std::string animDataPath = "../../../art/"
	+ aiName
	+ ".xml";

	auto sprData = animationEngine.load(animDataPath.c_str());

	assert(sprData);

	auto spr = std::make_shared<AnimatedSprite>(sprData, smgr->getRootSceneNode(), smgr);
	spr->setAnchor(irr::core::vector3df(spr->getSize().Width/2, 0.f, spr->getSize().Height));
	animationEngine.addSprite(spr);

	std::shared_ptr<Actor> ai = std::make_shared<Actor>();

	// initialize state machine
	auto stateMachine = std::make_shared<AIStateMachine>(ai, HashedString("idle"));
	stateMachine->setTeamMembership(membershipSupplier->requestMembership());
	stateMachine->initStates();

	ai->setStateMachine(stateMachine);
	ai->setSprite(spr);
	aiEventSource->addListener(ai);

	ai->start();

	return ai;
}

} // end namespace vik
