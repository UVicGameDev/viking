#include "viking/AIStateMachine.hpp"
#include "viking/CombatSceneActorHelper.hpp"
#include "viking/DamageZoneCreationEvent.hpp"
#include <cassert>

namespace vik
{

AIStateMachine::AIStateMachine(const std::weak_ptr<Actor>& context, const HashedString& initialState):
ActorStateMachine(context, initialState)
{
}

void AIStateMachine::initStates()
{
	addState(HashedString("idle"),
			std::make_shared<AIIdleState>(getContext()));
}

void AIStateMachine::setTeamMembership(const TeamMembership* teamMembership)
{
	this->teamMembership = teamMembership;
}

bool AIStateMachine::onPreUpstreamEvent(const Event& e)
{
	// catch and decorate damage zone creation events to assign the proper team membership tag
	if (e.getType() == HashedString("DamageZoneCreationEvent"))
	{
		const DamageZoneCreationEvent& dzce = static_cast<const DamageZoneCreationEvent&>(e);
		return handleUpstreamDamageZoneCreationEvent(dzce, teamMembership, *this);
	}
	else
	{
		return false;
	}
}

bool AIStateMachine::onPreDownstreamEvent(const Event& e)
{
	if (e.getType() == HashedString("DamageZoneCreationEvent"))
	{
		const DamageZoneCreationEvent& dzce = static_cast<const DamageZoneCreationEvent&>(e);
		return handleDownstreamDamageZoneCreationEvent(dzce, teamMembership, getContext().lock()->getSprite()->getTransformedBoundingBox());
	}
	else
	{
		return false;
	}
}

} // end namespace vik
