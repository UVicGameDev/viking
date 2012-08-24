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
#include "viking/DamageZoneCreationEvent.hpp"
#include <irrlicht/irrlicht.h>
#include <iostream>
#include <cassert>

using namespace irr;

namespace vik
{

CombatScene::CombatScene()
{
	PlayerFactoryCreationParams pfParams(HashedString("player"), this, animationEngine);
	playerFactory = new PlayerFactory(pfParams);

	aiFactory = new AIFactory(HashedString("ai"), this, animationEngine);

	TeamProperties playerTeamProperties(1, "players");
	playerTeam = new Team(playerTeamProperties);

	TeamProperties enemyTeamProperties(2, "enemies");
	enemyTeam = new Team(enemyTeamProperties);
}

CombatScene::~CombatScene()
{
	delete enemyTeam;
	delete playerTeam;

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
	PlayerFactoryConfiguration p1config("artsie", p1controlScheme, playerTeam);
	playerFactory->setConfiguration(p1config);
	auto artsie = playerFactory->create();
	objectEngine.addObject(artsie);
	artsie->addListener(shared_from_this());

	PlayerFactoryConfiguration p2config("player", p2controlScheme, playerTeam);
	playerFactory->setConfiguration(p2config);
	auto engie = playerFactory->create();
	objectEngine.addObject(engie);
	engie->addListener(shared_from_this());

	aiFactory->setConfiguration("sandbag", enemyTeam);
	auto sandbag = aiFactory->create();
	objectEngine.addObject(sandbag);
	sandbag->addListener(shared_from_this());

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

	GameObjectEngineTypeQuery actorQuery(&objectEngine);
	std::vector<std::shared_ptr<Actor>> actorList = actorQuery.getGameObjectsOfType<Actor>();

	video::IVideoDriver* driver = GameApp::getSingleton().getVideoDriver();

	for (auto it = actorList.begin(); it != actorList.end(); ++it)
	{
		driver->draw3DBox((*it)->getSprite()->getTransformedBoundingBox());
	}

	for (size_t i = 0; i < renderBoxOnceDebugQueue.size(); ++i)
	{
		driver->draw3DBox(renderBoxOnceDebugQueue[i], video::SColor(0xFFFF0000));
	}
	renderBoxOnceDebugQueue.clear();
}

bool CombatScene::onEvent(const Event& e)
{
	if (e.getType() == HashedString("DamageZoneCreationEvent"))
	{
		handleDamageZoneCreation(static_cast<const DamageZoneCreationEvent&>(e));
		return true;
	}
	else
	{
		return distributeEvent(e);
	}
}

void CombatScene::handleDamageZoneCreation(const DamageZoneCreationEvent& e)
{
	renderBoxOnceDebugQueue.push_back(e.getDamageZoneBounds());

	// send event back downstream so everybody can react to the damage zone
	distributeEvent(e);

	/*
	GameObjectEngineTypeQuery actorQuery(&objectEngine);
	std::vector<std::shared_ptr<Actor>> actorList = actorQuery.getGameObjectsOfType<Actor>();

	for (auto it = actorList.begin(); it != actorList.end(); ++it)
	{
		const core::aabbox3df& sprbox = (*it)->getSprite()->getTransformedBoundingBox();
		const core::aabbox3df& dmgbox = e.getDamageZoneBounds();
		if (sprbox.intersectsWithBox(dmgbox))
		{
			std::cout << "Collision!" << std::endl
			<< "Sprite: " << sprbox << std::endl
			<< "Damage: " << dmgbox << std::endl;
		}
	}
	*/
}

void CombatScene::updateCamera()
{
	GameObjectEngineTypeQuery actorQuery(&objectEngine);
	std::vector<std::shared_ptr<Actor>> actorList = actorQuery.getGameObjectsOfType<Actor>();
	core::aabbox3df actorViewBounds(core::vector3df(0,0,0));

	for (auto it = actorList.begin(); it != actorList.end(); ++it)
	{
		core::vector3df newpt = (*it)->getParticle().getPosition();
		actorViewBounds.addInternalPoint(newpt);
	}

	if (actorList.size() != 0)
	{
		core::vector3df averagePosition = actorViewBounds.getCenter();
		scene::ICameraSceneNode* cam = GameApp::getSingleton().getSceneManager()->getActiveCamera();
		const core::vector3df& oldpos(cam->getPosition());
		cam->setPosition(core::vector3df(averagePosition.X, oldpos.Y, oldpos.Z));
		cam->setTarget(cam->getPosition() + core::vector3df(0,-1,-1));
	}
}

} // end namespace vik
