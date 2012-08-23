#include "viking/DamageZoneCreationEvent.hpp"
#include <irrlicht/aabbox3d.h>

namespace vik
{

DamageZoneCreationEvent::DamageZoneCreationEvent(
		const std::shared_ptr<EventSource>& sender,
		const irr::core::aabbox3df& damageZoneBounds,
		irr::u32 damageToInflict):
Event(sender),
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


} // end namespace vik
