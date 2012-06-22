#include "viking/CombatScene.hpp"
#include "viking/PlayerFactory.hpp"
#include "viking/GameApp.hpp"
#include <irrlicht/irrlicht.h>

namespace vik
{

static void update_camera(irr::scene::ICameraSceneNode* cam, const KeyMap& keys)
{
	using namespace irr;

	core::vector3df oldpos = cam->getPosition();

	if (keys.isKeyDown(KEY_UP))
	{
		--oldpos.Z;
	}

	if (keys.isKeyDown(KEY_DOWN))
	{
		++oldpos.Z;
	}

	if (keys.isKeyDown(KEY_LEFT))
	{
		--oldpos.X;
	}

	if (keys.isKeyDown(KEY_RIGHT))
	{
		++oldpos.X;
	}

	cam->setPosition(oldpos);
}

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
	auto pf = std::make_shared<PlayerFactory>(HashedString("TestPlayer"), this);

	// give away ownership to the objectEngine
	objectEngine.addFactory(pf);
	
	// create one player for testing
	std::shared_ptr<GameObject> player = objectEngine.create(HashedString("TestPlayer"));
}

void CombatScene::onUpdate(GameTime& time)
{
	objectEngine.update(time);

	// temporary function to demo camera movement
	update_camera(GameApp::getSingleton().getSceneManager()->getActiveCamera(), GameApp::getSingleton().getKeyMap());
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

} // end namespace vik
