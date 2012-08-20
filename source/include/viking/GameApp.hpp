#ifndef VIK_GAMEAPP_HPP_INCLUDED
#define VIK_GAMEAPP_HPP_INCLUDED

#include <irrlicht/irrlicht.h>
#include "viking/EventSource.hpp"
#include "viking/GameObjectEngine.hpp"
#include "viking/GameTime.hpp"
#include "viking/KeyMap.hpp"
#include "viking/GameStateMachine.hpp"

namespace vik
{

// Class to wrap the global context of the application.
// The true main() function belongs to this class, and it is the one that distributes irrlicht events to all other event listeners in the game.
// Although it has singleton-like functions, it is not actually a singleton. It cannot be refered to in a static context, only once the real main has started.
class GameApp : public irr::IEventReceiver
{
public:
	// forced trivial destructor because it's a singleton.
	// Put code in onDestroy() instead.
	~GameApp() = default;

	// main loop of game
	void main();
	// distributes irrlicht callback for events
	bool OnEvent(const irr::SEvent& event);

	static GameApp& getSingleton();

	irr::IrrlichtDevice* getDevice();
	irr::video::IVideoDriver* getVideoDriver();
	irr::scene::ISceneManager* getSceneManager();
	irr::gui::IGUIEnvironment* getGUIEnvironment();
	irr::ILogger* getLogger();
	irr::ITimer* getTimer();
	KeyMap& getKeyMap();
private:
	// forced trivial constructor because it's a singleton.
	// Put code in onInit() instead.
	GameApp() = default;

	// pointer to most recently created instance of GameApp. Not exactly a static singleton.
	static GameApp* singleton;

	// interface for the irrlicht library
	irr::IrrlichtDevice* device;

	bool onInit();
	void onDestroy();

	// manages the current scene of the game
	std::shared_ptr<GameStateMachine> gameStateMachine;

	// distributes events to event listeners at the highest level
	EventSource rootEventSource;

	// remembers the current state of all keys
	std::shared_ptr<KeyMap> keyMap;

	// wrapper timer which keeps track of the time for the irrlicht engine
	GameTime rootTime;
};

} // end namespace vik

#endif // GAMEAPP_HPP_INCLUDED
