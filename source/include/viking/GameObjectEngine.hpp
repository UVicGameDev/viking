#ifndef VIK_GAMEOBJECTENGINE_HPP_INCLUDED
#define VIK_GAMEOBJECTENGINE_HPP_INCLUDED

#include <list>
#include <memory>
#include "viking/GameTime.hpp"
#include "viking/GameObject.hpp"

namespace vik
{

class GameObject;
class GameTime;

// manages a collection of objects and encapsulates their creation using factories
class GameObjectEngine
{
public:
	friend class GameObjectEngineIterator;

	// updates all objects
	void update(GameTime& time);

	// the object engine shares ownership of the objects added to it.
	// asserts in debug builds if an item is added twice
	void addObject(const std::shared_ptr<GameObject>& object);

	// removes object from set and therefore decrements reference count
	// in debug builds, asserts if object is not found.
	void removeObject(const std::shared_ptr<GameObject>& object);
private:
	std::list<std::shared_ptr<GameObject>> objectList;
};

} // end namespace vik

#endif // VIK_GAMEOBJECTENGINE_HPP_INCLUDED
