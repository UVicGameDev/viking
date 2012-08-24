#include "viking/PlayerStateMachine.hpp"
#include "viking/DamageZoneCreationEvent.hpp"
#include "viking/CombatSceneActorHelper.hpp"
#include <cassert>

namespace vik
{

PlayerStateMachine::PlayerStateMachine(const std::weak_ptr<Actor>& context, const HashedString& initialState, const ControlScheme& controlScheme):
ActorStateMachine(context, initialState),
controlScheme(controlScheme)
{
}

void PlayerStateMachine::initStates()
{
	addState(HashedString("idle"),
			std::make_shared<PlayerIdleState>(getContext(), controlScheme));
	addState(HashedString("mobile"),
			std::make_shared<PlayerMobileState>(getContext(), controlScheme));
	addState(HashedString("attacking"),
			std::make_shared<PlayerAttackingState>(getContext(), controlScheme));
}

void PlayerStateMachine::setTeamMembership(const TeamMembership* teamMembership)
{
	this->teamMembership = teamMembership;
}

bool PlayerStateMachine::onPreUpstreamEvent(const Event& e)
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

bool PlayerStateMachine::onPreDownstreamEvent(const Event& e)
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
