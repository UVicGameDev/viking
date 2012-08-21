#ifndef VIK_GAMEOBJECTFACTORY_HPP_INCLUDED
#define VIK_GAMEOBJECTFACTORY_HPP_INCLUDED

#include "viking/HashedString.hpp"
#include <memory>

namespace vik
{

class GameObject;

class GameObjectFactory
{
public:
	// factoryID is used to identify factories in polymorphic contexts
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
