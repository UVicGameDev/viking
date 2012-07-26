#include "viking/GameApp.hpp"
#include "viking/Actor.hpp"
#include <irrlicht/irrlicht.h>
#include "viking/IrrlichtEvent.hpp"
#include "viking/CombatScene.hpp"
#include <iostream>
#include <sstream>
#include <memory>

using namespace irr;

namespace vik
{

GameApp* GameApp::singleton;

void GameApp::main()
{
	if(!onInit())
	{
		return;
	}

	// start root clock for duration of main loop
	rootTime.start();

	while (getDevice()->run())
	{
		// update clock without tick, because getDevice->run() does a tick.
		rootTime.updateWithoutTick();

		gameStateMachine->update(rootTime);

		if (getDevice()->isWindowActive())
		{
			getVideoDriver()->beginScene(true, true, video::SColor(255,0,0,0));
			gameStateMachine->onRedraw();

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

	gameStateMachine->endStateMachine();

	onDestroy();
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
	// ignore logging events because it crashes too often in the following ways:
	// 1) stack overflows from events logging events logging events logging events
	// 2) logging information while destroying things causing events to be sent to them
	else if (event.EventType == irr::EET_LOG_TEXT_EVENT)
	{
		return false;
	}

	// distribute event to all listeners
	return rootEventSource.onEvent(IrrlichtEvent(event));
}

bool GameApp::onInit()
{
	const std::vector<video::E_DRIVER_TYPE> supportedDrivers = {
		video::EDT_DIRECT3D9,
		video::EDT_DIRECT3D8,
		video::EDT_OPENGL,
		video::EDT_BURNINGSVIDEO,
		video::EDT_SOFTWARE
	};

	// init device
	for (unsigned i = 0; (!device) && i < supportedDrivers.size(); ++i)
	{
		device = createDevice(video::EDT_OPENGL, core::dimension2du(640, 480), 32, false, false, true);
	}
	if (!device)
	{
		return false;
		std::cout << "Failed to create device." << std::endl;
	}

	rootTime.setTimer(getTimer());

	// must set event after creating the device
	// otherwise, will crash while trying to access
	// the device's timer while creating event time stamps.
	device->setEventReceiver(this);

	device->setWindowCaption(L"Viking");

	// init camera 
	scene::ICameraSceneNode* cam = device->getSceneManager()->addCameraSceneNode();
	cam->setTarget(core::vector3df(0.0f,0.0f,0.0f));
	cam->setPosition(core::vector3df(0.0f,100.0f,100.0f));
	cam->setUpVector(core::vector3df(0.0f, 0.0f, 1.0f));

	// init keymap
	keyMap = std::make_shared<KeyMap>();

	// draw a header with build creation date
	std::wstringstream ss;
	ss << L"Viking alpha. built on " << __DATE__;
	gui::IGUIStaticText* buildText = getGUIEnvironment()->addStaticText(ss.str().c_str(), core::recti(0,0,200,100));
	buildText->setOverrideColor(video::SColor(255,255,255,255));

	// hook up keyMap to its source of keyboard press events
	rootEventSource.addListener(keyMap);

	// create the game state machine and hook it up for events
	gameStateMachine = std::make_shared<GameStateMachine>();
	rootEventSource.addListener(gameStateMachine);

	// define initial scene of game
	gameStateMachine->startWithScene(std::make_shared<CombatScene>());

	return true;
}

void GameApp::onDestroy()
{
	device->drop();
}

GameApp& GameApp::getSingleton()
{
	if (!singleton)
	{
		singleton = new GameApp();
	}
	return *singleton;
}

irr::IrrlichtDevice* GameApp::getDevice()
{
	return device;
}

irr::video::IVideoDriver* GameApp::getVideoDriver()
{
	return getDevice()->getVideoDriver();
}

irr::scene::ISceneManager* GameApp::getSceneManager()
{
	return getDevice()->getSceneManager();
}

irr::gui::IGUIEnvironment* GameApp::getGUIEnvironment()
{
	return getDevice()->getGUIEnvironment();
}

irr::ILogger* GameApp::getLogger()
{
	return getDevice()->getLogger();
}

irr::ITimer* GameApp::getTimer()
{
	return getDevice()->getTimer();
}

KeyMap& GameApp::getKeyMap()
{
	return *(keyMap.get());
}

} // end namespace vik
