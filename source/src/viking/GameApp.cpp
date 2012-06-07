#include "viking/GameApp.hpp"
#include "viking/Actor.hpp"
#include "viking/PlayerFactory.hpp"
#include <irrlicht/irrlicht.h>
#include "viking/IrrlichtEvent.hpp"
#include <iostream>
#include <sstream>

using namespace irr;

namespace vik
{

GameApp* GameApp::instance;

GameApp::GameApp():
device(0)
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
	core::vector3df	oldrot = cam->getRotation();

	if (keys.isKeyDown(KEY_UP))
	{
		--oldpos.Z;
	}

	if(keys.isKeyDown(KEY_DOWN))
	{
		++oldpos.Z;
	}

	// The effect of rotation is not apparent because the sprite always faces you
	// Need to get a background in before we see a difference
	if(keys.isKeyDown(KEY_LEFT))
	{
		--oldrot.X;
	}

	if(keys.isKeyDown(KEY_RIGHT))
	{
		++oldrot.X;
	}

	cam->setPosition(oldpos);
	cam->setRotation(oldrot);
}

void GameApp::main()
{
	// hook up keymap with event source -- must remove at end of scope
	rootEventSource.addListener(&keyMap);

	GameObjectEngine objectEngine;

	PlayerFactory* pf = new PlayerFactory(HashedString("TestPlayer"), &rootEventSource);

	// give away ownership to the objectEngine
	objectEngine.addFactory(pf);
	pf->dropReference();
	
	// create one player for testing
	GameObject* player = objectEngine.create(HashedString("TestPlayer"));

	while (getDevice()->run())
	{
		controllerPanel.update(keyMap);

		objectEngine.update(rootTime);

		// temporary function to demo camera movement
		update_camera(getSceneManager()->getActiveCamera(), keyMap);

		if (getDevice()->isWindowActive())
		{
			getVideoDriver()->beginScene(true, true, video::SColor(255,100,149,237));

			getSceneManager()->drawAll();

			getGUIEnvironment()->drawAll();

			getVideoDriver()->endScene();
		}
		else
		{
			getDevice()->yield();
		}
	}

	rootEventSource.removeListener(&keyMap);
}

bool GameApp::OnEvent(const irr::SEvent& event)
{
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
	cam->setTarget(core::vector3df(0,0,0));
	cam->setPosition(core::vector3df(0,0,200));
}

} // end namespace vik
