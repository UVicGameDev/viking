#include "viking/ActorState.hpp"
#include "viking/Actor.hpp"

namespace vik
{

ActorState::ActorState(HashedString stateName, const std::weak_ptr<Actor>& context):
context(context),
stateName(stateName)
{
}

std::weak_ptr<Actor> ActorState::getContext()
{
	return context;
}

HashedString ActorState::getName() const
{
	return stateName;
}

} // end namespace vik

