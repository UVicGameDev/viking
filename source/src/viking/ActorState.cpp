#include "viking/ActorState.hpp"
#include "viking/Actor.hpp"

namespace vik
{

ActorState::ActorState(const std::weak_ptr<Actor>& context):
context(context)
{
}

std::weak_ptr<Actor> ActorState::getContext()
{
	return context;
}

} // end namespace vik

