#include "viking/GameObjectEngine.hpp"
#include "viking/GameApp.hpp"
#include <cassert>
#include <algorithm>
#include <iostream>

namespace vik
{

void GameObjectEngine::update(GameTime& time)
{
	for (std::list<std::shared_ptr<GameObject>>::iterator it = objectList.begin(); it != objectList.end(); ++it)
	{
		(*it)->update(time);
	}
}

void GameObjectEngine::addObject(const std::shared_ptr<GameObject>& object)
{
	assert(std::find(objectList.begin(), objectList.end(), object) == objectList.end());
	objectList.push_back(object);
}

void GameObjectEngine::removeObject(const std::shared_ptr<GameObject>& object)
{
	std::list<std::shared_ptr<GameObject>>::iterator it = std::find(objectList.begin(), objectList.end(), object);

	assert(it != objectList.end());
	objectList.erase(it);
}

void GameObjectEngine::addFactory(const std::shared_ptr<GameObjectFactory>& factory)
{
	assert(std::find(factoryList.begin(), factoryList.end(), factory) == factoryList.end());
	factoryList.push_back(factory);
}

void GameObjectEngine::removeFactory(const std::shared_ptr<GameObjectFactory>& factory)
{
	std::list<std::shared_ptr<GameObjectFactory>>::iterator it = std::find(factoryList.begin(), factoryList.end(), factory);

	assert(it != factoryList.end());
	factoryList.erase(it);
}

std::shared_ptr<GameObject> GameObjectEngine::create(HashedString factoryID)
{
	for (std::list<std::shared_ptr<GameObjectFactory>>::iterator it = factoryList.begin(); it != factoryList.end(); ++it)
	{
		if ((*it)->getFactoryID() == factoryID)
		{
			std::shared_ptr<GameObject> newObject = (*it)->create();
			addObject(newObject);
			return newObject;
		}
	}

	return std::shared_ptr<GameObject>();
}

} // end namespace vik
