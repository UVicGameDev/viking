#include "viking/GameStateMachine.hpp"

namespace vik
{

void GameStateMachine::startWithScene(const std::shared_ptr<Scene>& initialScene)
{
	currentScene = initialScene;
	currentScene->onEnter();
}

void GameStateMachine::switchToScene(const std::shared_ptr<Scene>& nextScene)
{
	currentScene->onLeave();
	currentScene = nextScene;
	currentScene->onEnter();
}

void GameStateMachine::endStateMachine()
{
	currentScene->onLeave();
	currentScene.reset();
}

void GameStateMachine::update(GameTime& time)
{
	currentScene->onUpdate(time);
}

void GameStateMachine::onRedraw()
{
	currentScene->onRedraw();
}

bool GameStateMachine::onEvent(const Event& e)
{
	return currentScene->onEvent(e);
}

} // end namespace vik
