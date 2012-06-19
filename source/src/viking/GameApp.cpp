#include "viking/GameApp.hpp"
#include "viking/Actor.hpp"
#include "viking/PlayerFactory.hpp"
#include <irrlicht/irrlicht.h>
#include "viking/IrrlichtEvent.hpp"
#include <iostream>
#include <sstream>
#include <memory>

using namespace irr;

namespace vik
{

GameApp* GameApp::instance;

GameApp::GameApp():
device(0),
keyMap(new KeyMap())
{
	initDevice();

	std::wstringstream ss;
	ss << L"Viking alpha. built on " << __DATE__;
	getGUIEnvironment()->addStaticText(ss.str().c_str(), core::recti(0,0,200,100));
}

GameApp::~GameApp()
{
	device->drop();
}

static void update_camera(scene::ICameraSceneNode* cam, const KeyMap& keys)
{
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
static void draw_axis(video::IVideoDriver* driver)
{
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

void GameApp::main()
{
	rootEventSource.addListener(keyMap);

	GameObjectEngine objectEngine;

	auto pf = std::make_shared<PlayerFactory>(HashedString("TestPlayer"), &rootEventSource);

	// give away ownership to the objectEngine
	objectEngine.addFactory(pf);
	
	// create one player for testing
	std::shared_ptr<GameObject> player = objectEngine.create(HashedString("TestPlayer"));

	// start root clock for duration of main loop
	rootTime.start();

	while (getDevice()->run())
	{
		// update clock without tick, because getDevice->run() does a tick.
		rootTime.updateWithoutTick();

		objectEngine.update(rootTime);

		// temporary function to demo camera movement
		update_camera(getSceneManager()->getActiveCamera(), *keyMap.get());

		if (getDevice()->isWindowActive())
		{
			getVideoDriver()->beginScene(true, true, video::SColor(255,100,149,237));

			draw_axis(getVideoDriver());

			getSceneManager()->drawAll();

			getGUIEnvironment()->drawAll();

			getVideoDriver()->endScene();
		}
		else
		{
			getDevice()->yield();
		}
	}

	rootTime.stop();

	rootEventSource.removeListener(keyMap);
}

bool GameApp::OnEvent(const irr::SEvent& event)
{
	// there is a bug in X11 where key input events are repeated. This code ensures that this case cannot happen.
	if (event.EventType == irr::EET_KEY_INPUT_EVENT)
	{
		if (keyMap->isKeyDown(event.KeyInput.Key) == event.KeyInput.PressedDown)
		{
			return false;
		}
	}

	// distribute event to all listeners
	return rootEventSource.onEvent(IrrlichtEvent(event));
}

void GameApp::initDevice()
{
	// init instance
	instance = this;

	// init device
	device = createDevice(video::EDT_OPENGL, core::dimension2du(640, 480), 32, false, false, true);

	rootTime.setTimer(getTimer());

	// must set event after creating the device
	// otherwise, will crash while trying to access
	// the device's timer while creating event time stamps.
	device->setEventReceiver(this);

	getDevice()->setWindowCaption(L"Viking");

	// init camera 
	scene::ICameraSceneNode* cam = getSceneManager()->addCameraSceneNode();
	cam->setTarget(core::vector3df(0.0f,0.0f,0.0f));
	cam->setPosition(core::vector3df(0.0f,100.0f,100.0f));
	cam->setUpVector(core::vector3df(0.0f, 0.0f, 1.0f));
}

} // end namespace vik
