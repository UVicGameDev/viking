#include "viking/DamageZoneCreationEvent.hpp"

namespace vik
{

DamageZoneCreationEvent::DamageZoneCreationEvent(
		const irr::core::aabbox3df& damageZoneBounds,
		irr::u32 damageToInflict):
damageZoneBounds(damageZoneBounds),
damageToInflict(damageToInflict)
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

HashedString DamageZoneCreationEvent::getType() const
{
	return HashedString("DamageZoneCreationEvent");
}

} // end namespace vik
