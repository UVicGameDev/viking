#include "viking/AIIdleState.hpp"

namespace vik
{

AIIdleState::AIIdleState(const std::weak_ptr<Actor>& context):
ActorState(context)
{
}

void AIIdleState::onEnter()
{
	getContext().lock()->getSprite()->play(HashedString("idle"));
}

} // end namespace vik
