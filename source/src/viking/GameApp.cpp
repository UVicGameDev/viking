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
	if (!onInit())
	{
		return;
	}

	// define initial scene of game
	gameStateMachine->startWithScene(std::make_shared<CombatScene>());

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
	return rootEventSource->onEvent(IrrlichtEvent(event));
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



	video::E_DRIVER_TYPE chosenDriver;
	device = 0;
	// init device
	for (size_t i = 0; i < supportedDrivers.size(); ++i)
	{
		chosenDriver = supportedDrivers[i];
		if (IrrlichtDevice::isDriverSupported(chosenDriver))
		{
			device = createDevice(chosenDriver, core::dimension2du(640, 480), 32, false, false, true);
			break;
		}
	}
	if (!device)
	{
		std::cout << "Failed to create device." << std::endl;
		return false;
	}

	if (chosenDriver == video::EDT_BURNINGSVIDEO || chosenDriver == video::EDT_SOFTWARE)
	{
		std::cout << "Warning: Could not find compatible version of Direct3D or OpenGL." << std::endl
		<< "Fell back to using a software device. Performance may be impacted." << std::endl;
	}

	sengine = irrklang::createIrrKlangDevice();
	if (!sengine)
	{
		std::cout << "Failed to create sound engine." << std::endl;
		return false;
	}

	rootTime.setTimer(getTimer());

	// must set event after creating the device
	// otherwise, will crash while trying to access
	// the device's timer while creating event time stamps.
	device->setEventReceiver(this);
	rootEventSource = std::make_shared<EventSource>();

	device->setWindowCaption(L"Viking");

	// init camera 
	scene::ICameraSceneNode* cam = device->getSceneManager()->addCameraSceneNode();
	cam->setUpVector(core::vector3df(0.0f, 0.0f, 1.0f));

	// init keymap
	keyMap = std::make_shared<KeyMap>();

	// draw a header with build creation date
	std::wstringstream ss;
	ss << L"Viking pre-alpha. built on " << __DATE__;
	gui::IGUIStaticText* buildText = getGUIEnvironment()->addStaticText(ss.str().c_str(), core::recti(0,0,200,100));
	buildText->setOverrideColor(video::SColor(255,255,255,255));

	// hook up keyMap to its source of keyboard press events
	rootEventSource->addListener(keyMap);

	// create the game state machine and hook it up for events
	gameStateMachine = std::make_shared<GameStateMachine>();
	rootEventSource->addListener(gameStateMachine);

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

irrklang::ISoundEngine* GameApp::getSoundEngine()
{
	return sengine;
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

std::shared_ptr<KeyMap>& GameApp::getKeyMap()
{
	return keyMap;
}

std::shared_ptr<GameStateMachine>& GameApp::getGameStateMachine()
{
	return gameStateMachine;
}

} // end namespace vik
