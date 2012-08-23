#ifndef VIK_DAMAGEZONECREATIONEVENT_HPP_INCLUDED
#define VIK_DAMAGEZONECREATIONEVENT_HPP_INCLUDED

#include "viking/Event.hpp"
#include <irrlicht/aabbox3d.h>

namespace vik
{

class DamageZoneCreationEvent : public Event
{
public:
	DamageZoneCreationEvent(const std::shared_ptr<EventSource>& sender,
			const irr::core::aabbox3df& damageZoneBounds,
			irr::u32 damageToInflict);

	const irr::core::aabbox3df& getDamageZoneBounds() const;
	irr::u32 getDamageToInflict() const;
	HashedString getType() const override;
private:
	irr::core::aabbox3df damageZoneBounds;
	irr::u32 damageToInflict;
};

} // end namespace vik

#endif // VIK_DAMAGEZONECREATIONEVENT_HPP_INCLUDED
