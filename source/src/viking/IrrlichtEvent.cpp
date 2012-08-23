#include "viking/IrrlichtEvent.hpp"

namespace vik
{

IrrlichtEvent::IrrlichtEvent(const std::shared_ptr<EventSource>& sender, const irr::SEvent& e):
Event(sender),
ievent(e)
{
}

const irr::SEvent& IrrlichtEvent::getEvent() const
{
	return ievent;
}

HashedString IrrlichtEvent::getType() const
{
	return HashedString("IrrlichtEvent");
}

} // end namespace vik
