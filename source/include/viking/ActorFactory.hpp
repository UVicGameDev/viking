#ifndef VIK_ACTORFACTORY_HPP_INCLUDED
#define VIK_ACTORFACTORY_HPP_INCLUDED

#include "viking/HashedString.hpp"
#include <memory>

namespace vik
{

class Actor;

class ActorFactory
{
public:
	// factoryID is used to identify factories in polymorphic contexts
	ActorFactory(HashedString factoryID);
	virtual ~ActorFactory(){}

	// allocate and construct new instance of an Actor
	virtual std::shared_ptr<Actor> create() = 0;

	HashedString getFactoryID() const; 
private:
	HashedString factoryID;
};

} // end namespace vik

#endif // VIK_ACTORFACTORY_HPP_INCLUDED
