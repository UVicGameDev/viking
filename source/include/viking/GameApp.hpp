#ifndef VIK_GAMEAPP_HPP_INCLUDED
#define VIK_GAMEAPP_HPP_INCLUDED

#include <irrlicht/irrlicht.h>
#include <irrklang/irrKlang.h>
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

	// top level irrlicht structure
	irr::IrrlichtDevice* getDevice();

	// irrklang sound engine
	irrklang::ISoundEngine* getSoundEngine();

	// used for low level rendering and changing video settings
	irr::video::IVideoDriver* getVideoDriver();

	// used to create and manage ISceneNodes
	irr::scene::ISceneManager* getSceneManager();

	// used to create and manage IGUIElements
	irr::gui::IGUIEnvironment* getGUIEnvironment();

	// used to log messages, which can be displayed on the console and saved to a file.
	irr::ILogger* getLogger();

	// used to know information about the global timeline
	// note that GameTime is a wrapper around this information.
	// GameTime should be preferred over using this.
	irr::ITimer* getTimer();
	
	// used to check the current state of keys without needing events
	std::shared_ptr<KeyMap>& getKeyMap();

	// used to manage scene transitions
	std::shared_ptr<GameStateMachine>& getGameStateMachine();
private:
	// forced trivial constructor because it's a singleton.
	// Put code in onInit() instead.
	GameApp() = default;

	// pointer to most recently created instance of GameApp. Not exactly a static singleton.
	static GameApp* singleton;

	// interface for the irrlicht library
	irr::IrrlichtDevice* device;
	
	// interface for the irrklang library
	irrklang::ISoundEngine* sengine;

	bool onInit();
	void onDestroy();

	// manages the current scene of the game
	std::shared_ptr<GameStateMachine> gameStateMachine;

	// distributes events to event listeners at the highest level
	std::shared_ptr<EventSource> rootEventSource;

	// remembers the current state of all keys
	std::shared_ptr<KeyMap> keyMap;

	// wrapper timer which keeps track of the time for the irrlicht engine
	GameTime rootTime;
};

} // end namespace vik

#endif // GAMEAPP_HPP_INCLUDED
