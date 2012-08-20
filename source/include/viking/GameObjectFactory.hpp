#ifndef VIK_GAMEOBJECTFACTORY_HPP_INCLUDED
#define VIK_GAMEOBJECTFACTORY_HPP_INCLUDED

#include "viking/HashedString.hpp"
#include <memory>

namespace vik
{

class GameObject;

// interface for defining how game objects are created
class GameObjectFactory
{
public:
	// factoryID is used to make calls to this factory at runtime
	// Each factory in a GameObjectEngine should have a unique ID
	GameObjectFactory(HashedString factoryID);
	virtual ~GameObjectFactory(){}

	// allocate and construct new instance of a GameObject subclass
	virtual std::shared_ptr<GameObject> create() = 0;

	HashedString getFactoryID() const; 
private:
	HashedString factoryID;
};

} // end namespace vik

#endif // VIK_GAMEOBJECTFACTORY_HPP_INCLUDED
