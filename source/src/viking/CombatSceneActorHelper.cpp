#include "viking/CombatSceneActorHelper.hpp"
#include "viking/DamageZoneCreationEvent.hpp"
#include "viking/TeamMembership.hpp"
#include "viking/ActorStateMachine.hpp"
#include "viking/GameApp.hpp"
#include "viking/AnimatedSprite.hpp"
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
		const irr::core::aabbox3df& actorHitBox,
		AnimatedSprite& actorSprite)
{
	// damage only happens if you're on different teams
	if (actorTeamMembership->getTeam() != e.getInflictorMembership()->getTeam())
	{
		if (actorHitBox.intersectsWithBox(e.getDamageZoneBounds()))
		{

			GameApp::getSingleton().getSoundEngine()->play2D("../../../art/punch.wav");
			actorSprite.toggleFlipHorizontal();
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
