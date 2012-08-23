#include "viking/ActorFactory.hpp"

namespace vik
{

ActorFactory::ActorFactory(HashedString factoryID):
factoryID(factoryID)
{
}

HashedString ActorFactory::getFactoryID() const
{
	return factoryID;
}

} // end namespace vik
