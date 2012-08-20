#ifndef VIK_GAMEOBJECTENGINETYPEQUERY_HPP_INCLUDED
#define VIK_GAMEOBJECTENGINETYPEQUERY_HPP_INCLUDED

#include <vector>
#include <memory>
#include "viking/GameObjectEngineIterator.hpp"
#include "viking/GameObjectEngine.hpp"
#include "viking/Actor.hpp"

namespace vik
{

// Uses RTTI to find all Actors in the GameObjectEngine
class GameObjectEngineTypeQuery
{
public:
	GameObjectEngineTypeQuery(GameObjectEngine* engine);
	template<class T>
	std::vector<std::shared_ptr<T>> getGameObjectsOfType();
private:
	GameObjectEngineIterator it;
};

template<class T>
std::vector<std::shared_ptr<T>> GameObjectEngineTypeQuery::getGameObjectsOfType()
{
	std::vector<std::shared_ptr<T>> objectList;
	it.reset();
	while (it.hasNext())
	{
		std::shared_ptr<GameObject> curr = it.next();
		if (auto casted = std::dynamic_pointer_cast<T>(curr))
		{
			objectList.push_back(casted);
		}
	}
	return objectList;
}

} // end namespace vik

#endif // VIK_GAMEOBJECTENGINETYPEQUERY_HPP_INCLUDED
