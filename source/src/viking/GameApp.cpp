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

GameApp* GameApp::instance;

GameApp::GameApp():
device(0),
keyMap(new KeyMap())
{
	initDevice();

	std::wstringstream ss;
	ss << L"Viking alpha. built on " << __DATE__;
	getGUIEnvironment()->addStaticText(ss.str().c_str(), core::recti(0,0,200,100));

	rootEventSource.addListener(keyMap);

	gameStateMachine = std::make_shared<GameStateMachine>();
	rootEventSource.addListener(gameStateMachine);

	gameStateMachine->startWithScene(std::make_shared<CombatScene>());
}

GameApp::~GameApp()
{
	device->drop();
}

void GameApp::main()
{

	// start root clock for duration of main loop
	rootTime.start();

	while (getDevice()->run())
	{
		// update clock without tick, because getDevice->run() does a tick.
		rootTime.updateWithoutTick();

		gameStateMachine->update(rootTime);

		if (getDevice()->isWindowActive())
		{
			getVideoDriver()->beginScene(true, true, video::SColor(255,100,149,237));
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
