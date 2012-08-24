#include "viking/CombatSceneActorHelper.hpp"
#include "viking/DamageZoneCreationEvent.hpp"
#include "viking/TeamMembership.hpp"
#include "viking/ActorStateMachine.hpp"
#include <iostream>

namespace vik
{

bool handleUpstreamDamageZoneCreationEvent(
		const DamageZoneCreationEvent& e,
		const TeamMembership* actorTeamMembership,
		ActorStateMachine& stateMachine)
{
	DamageZoneCreationEvent decorated(e.getDamageZoneBounds(), e.getDamageToInflict(), actorTeamMembership);

	// forward it upstream
	return stateMachine.distributeEvent(decorated);
}

bool handleDownstreamDamageZoneCreationEvent(
		const DamageZoneCreationEvent& e,
		const TeamMembership* actorTeamMembership,
		const irr::core::aabbox3df& actorHitBox)
{
	// damage only happens if you're on different teams
	if (actorTeamMembership->getTeam() != e.getInflictorMembership()->getTeam())
	{
		if (actorHitBox.intersectsWithBox(e.getDamageZoneBounds()))
		{
			std::cout << "Ouch!" << std::endl;
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}
}

} // end namespace vik
