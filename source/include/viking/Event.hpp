#ifndef VIK_EVENT_HPP_INCLUDED
#define VIK_EVENT_HPP_INCLUDED

#include <irrlicht/irrTypes.h>
#include "viking/HashedString.hpp"
#include <memory>

namespace vik
{

class EventSource;

// meant to be passed around by EventListeners and EventSources.
// Some type information is used to downcast to proper derived event type
class Event
{
public:
	friend class EventSource;

	Event();
	// return creation time of event 
	irr::u32 getTimeStamp() const;
	// return type name of event as a hashed string
	virtual HashedString getType() const = 0;
	// returns reference to last EventSource that called distributeEvent with this event
	const std::shared_ptr<EventSource>& getSender() const;
private:
	void setSender(const std::shared_ptr<EventSource>& sender) const;
	irr::u32 timeStamp;
	mutable std::shared_ptr<EventSource> sender;
};

} // end namespace vik

#endif // VIK_EVENT_HPP_INCLUDED
