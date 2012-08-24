#ifndef VIK_DAMAGEZONECREATIONEVENT_HPP_INCLUDED
#define VIK_DAMAGEZONECREATIONEVENT_HPP_INCLUDED

#include "viking/Event.hpp"
#include <irrlicht/aabbox3d.h>

namespace vik
{

class TeamMembership;

class DamageZoneCreationEvent : public Event
{
public:
	DamageZoneCreationEvent(
			const irr::core::aabbox3df& damageZoneBounds,
			irr::u32 damageToInflict,
			const TeamMembership* inflictorMembership
			);

	const irr::core::aabbox3df& getDamageZoneBounds() const;
	irr::u32 getDamageToInflict() const;

	void setInflictorMembership(const TeamMembership* inflictorMembership);
	const TeamMembership* getInflictorMembership() const;

	HashedString getType() const override;
private:
	irr::core::aabbox3df damageZoneBounds;
	irr::u32 damageToInflict;
	const TeamMembership* inflictorMembership;
};

} // end namespace vik

#endif // VIK_DAMAGEZONECREATIONEVENT_HPP_INCLUDED
