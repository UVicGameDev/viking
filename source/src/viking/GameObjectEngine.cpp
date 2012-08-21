#include "viking/GameObjectEngine.hpp"
#include <cassert>
#include <algorithm>
#include <iostream>

namespace vik
{

void GameObjectEngine::update(GameTime& time)
{
	// TODO: Must handle the case where an object is removed from the list during iteration. 
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

} // end namespace vik
