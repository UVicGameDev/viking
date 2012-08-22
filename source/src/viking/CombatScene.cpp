#include "viking/CombatScene.hpp"
#include "viking/PlayerFactory.hpp"
#include "viking/AIFactory.hpp"
#include "viking/GameApp.hpp"
#include "viking/PaperSceneNodeFactory.hpp"
#include "viking/GameObjectEngineTypeQuery.hpp"
#include "viking/Actor.hpp"
#include "viking/IrrlichtStream.hpp"
#include "viking/IrrlichtHelper.hpp"
#include "viking/DebugRender.hpp"
#include "viking/FPSDisplay.hpp"
#include "viking/PlayerFactoryCreationParams.hpp"
#include <irrlicht/irrlicht.h>
#include <iostream>

using namespace irr;

namespace vik
{

CombatScene::CombatScene()
{
	PlayerFactoryCreationParams pfParams(HashedString("player"), this, animationEngine);
	playerFactory = new PlayerFactory(pfParams);

	aiFactory = new AIFactory(HashedString("ai"), this, animationEngine);
}

CombatScene::~CombatScene()
{
	delete aiFactory;
	delete playerFactory;
}

void CombatScene::onEnter()
{
	ControlScheme p1controlScheme(
			irr::KEY_UP,
			irr::KEY_DOWN,
			irr::KEY_LEFT,
			irr::KEY_RIGHT,
			irr::KEY_DELETE);

	ControlScheme p2controlScheme(
			irr::KEY_KEY_W,
			irr::KEY_KEY_S,
			irr::KEY_KEY_A,
			irr::KEY_KEY_D,
			irr::KEY_KEY_G);

	// create players for testing
	PlayerFactoryConfiguration p1config("artsie", p1controlScheme);
	playerFactory->setConfiguration(p1config);
	auto artsie = playerFactory->create();
	objectEngine.addObject(artsie);

	PlayerFactoryConfiguration p2config("player", p2controlScheme);
	playerFactory->setConfiguration(p2config);
	auto engie = playerFactory->create();
	objectEngine.addObject(engie);

	auto sandbag = aiFactory->create();
	objectEngine.addObject(sandbag);

	// create FPS display thingy
	auto fpsDisplay = std::make_shared<FPSDisplay>();
	objectEngine.addObject(fpsDisplay);

	scene::ISceneManager* smgr = GameApp::getSingleton().getSceneManager();
	video::IVideoDriver* driver = GameApp::getSingleton().getVideoDriver();

	PaperSceneNodeFactory paperFactory(smgr);
	scene::ISceneNode* floorNode = paperFactory.create(driver->getTexture("../../../art/ground.png"));
	core::aabbox3df bbox = floorNode->getTransformedBoundingBox();

	GameApp::getSingleton().getSceneManager()->getActiveCamera()->setPosition(core::vector3df(bbox.getExtent().X/2, 1.2 * bbox.getExtent().Y , bbox.getExtent().Y));
}

void CombatScene::onUpdate(GameTime& time)
{
	objectEngine.update(time);

	animationEngine.update(time);

	updateCamera();
}

void CombatScene::onLeave()
{
	GameApp::getSingleton().getSceneManager()->clear();
}

void CombatScene::onRedraw()
{
	drawRGBAxis();
}

bool CombatScene::onEvent(const Event& e)
{
	return distributeEvent(e);
}

void CombatScene::updateCamera()
{
	core::vector3df averagePosition;

	GameObjectEngineTypeQuery actorQuery(&objectEngine);
	std::vector<std::shared_ptr<Actor>> actorList = actorQuery.getGameObjectsOfType<Actor>();

	for (auto it = actorList.begin(); it != actorList.end(); ++it)
	{
		averagePosition += (*it)->getParticle().getPosition();
	}

	if (actorList.size() != 0)
	{
		averagePosition /= actorList.size();
		scene::ICameraSceneNode* cam = GameApp::getSingleton().getSceneManager()->getActiveCamera();
		const core::vector3df& oldpos(cam->getPosition());
		cam->setPosition(core::vector3df(averagePosition.X, oldpos.Y, oldpos.Z));
		cam->setTarget(cam->getPosition() + core::vector3df(0,-1,-1));
	}
}

} // end namespace vik
