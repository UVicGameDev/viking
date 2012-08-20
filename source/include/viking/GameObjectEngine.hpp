#ifndef VIK_GAMEOBJECTENGINE_HPP_INCLUDED
#define VIK_GAMEOBJECTENGINE_HPP_INCLUDED

#include <list>
#include <memory>
#include "viking/GameTime.hpp"
#include "viking/GameObject.hpp"
#include "viking/GameObjectFactory.hpp"

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

	// the list of objects is implemented as a set. Therefore, each object can only exist in the object engine once at a time. 
	// the object engine shares ownership of the objects added to it.
	// asserts in debug builds if an item is added twice
	void addObject(const std::shared_ptr<GameObject>& object);

	// removes object from set and therefore decrements reference count
	// in debug builds, asserts if object is not found.
	void removeObject(const std::shared_ptr<GameObject>& object);

	// factories are stored as a set, therefore only one instance of each factory can be added at once.
	// ownership of factories added is shared with the object engine.
	// will assert in debug builds if the factory is there/not there when it shouldn't/should
	void addFactory(const std::shared_ptr<GameObjectFactory>& factory);

	// removes factory from set and therefore decrements reference count
	void removeFactory(const std::shared_ptr<GameObjectFactory>& factory);

	// find factory associated with ID and return object created by it
	// the ownership of objects created by this method is shared with the GameObjectEngine called.
	// the objects created are automatically added to the game object engine
	// will return a null pointer if the factory is not found 
	std::shared_ptr<GameObject> create(HashedString factoryID);
private:
	std::list<std::shared_ptr<GameObject>> objectList;
	std::list<std::shared_ptr<GameObjectFactory>> factoryList;
};

} // end namespace vik

#endif // VIK_GAMEOBJECTENGINE_HPP_INCLUDED
