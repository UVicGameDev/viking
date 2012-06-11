#include "viking/GameObjectEngine.hpp"
#include "viking/GameApp.hpp"
#include <cassert>
#include <algorithm>

namespace vik
{

GameObjectEngine::~GameObjectEngine()
{
}

void GameObjectEngine::update(GameTime& time)
{
	for (std::set<std::shared_ptr<GameObject>>::iterator it = objectList.begin(); it != objectList.end(); ++it)
	{
		(*it)->update(time);
	}
}

void GameObjectEngine::addObject(const std::shared_ptr<GameObject>& object)
{
	assert(objectList.find(object) == objectList.end());
	objectList.insert(object);
}

void GameObjectEngine::removeObject(const std::shared_ptr<GameObject>& object)
{
	std::set<std::shared_ptr<GameObject>>::iterator it = objectList.find(object);
	assert(it != objectList.end());
	objectList.erase(it);
}

void GameObjectEngine::addFactory(const std::shared_ptr<GameObjectFactory>& factory)
{
	assert(factoryList.find(factory) == factoryList.end());
	factoryList.insert(factory);
}

void GameObjectEngine::removeFactory(const std::shared_ptr<GameObjectFactory>& factory)
{
	std::set<std::shared_ptr<GameObjectFactory>>::iterator it = factoryList.find(factory);
	assert(it != factoryList.end());
	factoryList.erase(it);
}

std::shared_ptr<GameObject> GameObjectEngine::create(HashedString factoryID)
{
	for (std::set<std::shared_ptr<GameObjectFactory>>::iterator it = factoryList.begin(); it != factoryList.end(); ++it)
	{
		if ((*it)->getFactoryID() == factoryID)
		{
			std::shared_ptr<GameObject> newObject = (*it)->create();
			return newObject;
		}
	}

	return std::shared_ptr<GameObject>();
}

} // end namespace vik
