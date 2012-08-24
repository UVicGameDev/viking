#ifndef VIK_COMBATSCENEACTORHELPER_HPP_INCLUDED
#define VIK_COMBATSCENEACTORHELPER_HPP_INCLUDED

#include <irrlicht/aabbox3d.h>

namespace vik
{

class DamageZoneCreationEvent;
class TeamMembership;
class ActorStateMachine;

bool handleDownstreamDamageZoneCreationEvent(
		const DamageZoneCreationEvent& e,
		const TeamMembership* actorTeamMembership,
		const irr::core::aabbox3df& actorHitBox);

bool handleUpstreamDamageZoneCreationEvent(
		const DamageZoneCreationEvent& e,
		const TeamMembership* actorTeamMembership,
		ActorStateMachine& stateMachine);

} // end namespace vik

#endif // VIK_COMBATSCENEACTORHELPER_HPP_INCLUDED
