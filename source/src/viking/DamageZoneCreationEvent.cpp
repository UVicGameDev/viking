#include "viking/DamageZoneCreationEvent.hpp"
#include "viking/TeamMembership.hpp"

namespace vik
{

DamageZoneCreationEvent::DamageZoneCreationEvent(
		const irr::core::aabbox3df& damageZoneBounds,
		irr::u32 damageToInflict,
		const TeamMembership* inflictorMembership):
damageZoneBounds(damageZoneBounds),
damageToInflict(damageToInflict),
inflictorMembership(inflictorMembership)
{
}

const irr::core::aabbox3df& DamageZoneCreationEvent::getDamageZoneBounds() const
{
	return damageZoneBounds;
}

irr::u32 DamageZoneCreationEvent::getDamageToInflict() const
{
	return damageToInflict;
}

void DamageZoneCreationEvent::setInflictorMembership(const TeamMembership* inflictorMembership)
{
	this->inflictorMembership = inflictorMembership;
}

const TeamMembership* DamageZoneCreationEvent::getInflictorMembership() const
{
	return inflictorMembership;
}

HashedString DamageZoneCreationEvent::getType() const
{
	return HashedString("DamageZoneCreationEvent");
}

} // end namespace vik
