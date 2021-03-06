#ifndef VIK_EVENTSOURCE_HPP_INCLUDED
#define VIK_EVENTSOURCE_HPP_INCLUDED

#include <list>
#include <memory>
#include "viking/EventListener.hpp"

namespace vik
{

class Event;

// Forwards events received to a list of EventListeners
class EventSource : public EventListener, public std::enable_shared_from_this<EventSource>
{
public:
	// distributes Event to all listeners using distributeEvent() function.
	bool onEvent(const Event& event);
	// adds listener to list of subscribers. Note that it is possible to add something twice (does not use set behaviour)
	void addListener(const std::weak_ptr<EventListener>& listener);
	// removes listener. Will assert in debug builds if the listener is not in the list.
	void removeListener(const std::weak_ptr<EventListener>& listener);

	// distributes Event to all listeners
	bool distributeEvent(const Event& e);
private:
	std::list<std::weak_ptr<EventListener>> listeners;
};

} // end namespace vik

#endif // VIK_EVENTSOURCE_HPP_INCLUDED
