#include "viking/CombatScene.hpp"
#include "viking/PlayerFactory.hpp"
#include "viking/GameApp.hpp"
#include "viking/PaperSceneNodeFactory.hpp"
#include "viking/GameObjectEngineTypeQuery.hpp"
#include "viking/Actor.hpp"
#include "viking/IrrlichtStream.hpp"
#include "viking/FPSDisplay.hpp"
#include <irrlicht/irrlicht.h>
#include <iostream>

using namespace irr;

namespace vik
{

// draws red green blue arrows to help know how the X Y Z coordinates work
static void draw_axis(irr::video::IVideoDriver* driver)
{
	using namespace irr;

	const float axisLength = 100.0f;
	const core::vector3df center(0.0f);
	const core::vector3df arrows[] = {
		center + core::vector3df(axisLength, 0.0f, 0.0f),
		center + core::vector3df(0.0f, axisLength, 0.0f),
		center + core::vector3df(0.0f, 0.0f, axisLength)
	};
	const video::SColor arrow_colors[] = {
		video::SColor(255, 255,   0,   0),
		video::SColor(255,   0, 255,   0),
		video::SColor(255,   0,   0, 255)
	};
	
	video::SMaterial material;
	material.Lighting = false;
	driver->setMaterial(material);
	driver->setTransform(video::ETS_WORLD, core::IdentityMatrix);

	driver->draw3DBox( core::aabbox3df(0.0f,0.0f,0.0f,20.0f,20.0f,20.0f) , video::SColor(255, 255, 255, 255) );
	for (unsigned i = 0; i < sizeof(arrows)/sizeof(*arrows); ++i)
	{
		driver->draw3DLine(center, arrows[i], arrow_colors[i % (sizeof(arrow_colors)/(sizeof(*arrow_colors)))]);
	}
}

void CombatScene::onEnter()
{
	auto pf = std::make_shared<PlayerFactory>(hashString("TestPlayer"), this);

	// give away ownership to the objectEngine
	objectEngine.addFactory(pf);
	
	// create one player for testing
	std::shared_ptr<GameObject> player = objectEngine.create(hashString("TestPlayer"));

	// create FPS display thingy
	auto fpsDisplay = std::make_shared<FPSDisplay>();
	objectEngine.addObject(fpsDisplay);

	scene::ISceneManager* smgr = GameApp::getSingleton().getSceneManager();
	video::IVideoDriver* driver = GameApp::getSingleton().getVideoDriver();

	PaperSceneNodeFactory paperFactory(smgr);
	scene::ISceneNode* floor = paperFactory.create(driver->getTexture("../../../art/ground.png"));
	core::aabbox3df bbox = floor->getTransformedBoundingBox();

	GameApp::getSingleton().getSceneManager()->getActiveCamera()->setPosition(core::vector3df(bbox.getExtent().X/2, bbox.getExtent().Y , bbox.getExtent().Y));
}

void CombatScene::onUpdate(GameTime& time)
{
	objectEngine.update(time);

	updateCamera();
}

void CombatScene::onLeave()
{
}

void CombatScene::onRedraw()
{
	draw_axis(GameApp::getSingleton().getVideoDriver());
}

bool CombatScene::onEvent(const Event& e)
{
	return distributeEvent(e);
}

/*
static core::aabbox3df getSceneNodeCompositeBounds(scene::ISceneNode* root)
{
	core::aabbox3df boundaries;
	if (root != GameApp::getSingleton().getSceneManager()->getRootSceneNode())
	{
		boundaries.addInternalBox(root->getTransformedBoundingBox());
	}
	for (auto it = root->getChildren().begin(); it != root->getChildren().end(); ++it)
	{
		std::cout << *it << std::endl;
		if ((*it)->isVisible())
		{
			boundaries.addInternalBox(getSceneNodeCompositeBounds(*it));
		}
	}
	return boundaries;
}
*/

void CombatScene::updateCamera()
{
	core::vector3df averagePosition;

	/*
	scene::ISceneNode* rootNode = GameApp::getSingleton().getSceneManager()->getRootSceneNode();

	core::aabbox3df sceneBounds = getSceneNodeCompositeBounds(rootNode);
	std::cout << "Scene bounds: { { " << sceneBounds.MinEdge.X << ", " << sceneBounds.MinEdge.Y << " } , { " << sceneBounds.MaxEdge.X << ", " << sceneBounds.MaxEdge.Y << " } }" << std::endl;
	*/

	GameObjectEngineTypeQuery actorQuery(&objectEngine);
	std::vector<std::shared_ptr<Actor>> actorList = actorQuery.getGameObjectsOfType<Actor>();

	for (auto it = actorList.begin(); it != actorList.end(); ++it)
	{
		averagePosition += (*it)->getParticle().getPosition();
	}

	if (actorList.size() != 0)
	{
		averagePosition /= actorList.size();
		GameApp::getSingleton().getSceneManager()->getActiveCamera()->setTarget(averagePosition);
	}

}

} // end namespace vik
