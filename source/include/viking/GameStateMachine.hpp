#ifndef GAMESTATEMACHINE_HPP_INCLUDED
#define GAMESTATEMACHINE_HPP_INCLUDED

#include "viking/GameTime.hpp"
#include "viking/EventListener.hpp"
#include "viking/Scene.hpp"
#include <memory>

namespace vik
{

class GameStateMachine : public EventListener
{
public:
	// start the scene manager's state machine with the given scene. Must be called before any updates.
	void startWithScene(const std::shared_ptr<Scene>& initialScene);

	// leave current scene and enter next scene
	void switchToScene(const std::shared_ptr<Scene>& nextScene);

	// deinitialize state machine
	void endStateMachine();

	// update current scene
	void update(GameTime& time);

	// called at the start of each draw
	void onRedraw();

	bool onEvent(const Event& e);
private:
	std::shared_ptr<Scene> currentScene;
};

} // end namespace vik

#endif // GAMESTATEMACHINE_HPP_INCLUDED
