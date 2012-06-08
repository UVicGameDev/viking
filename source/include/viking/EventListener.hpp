#ifndef EVENTLISTENER_HPP_INCLUDED
#define EVENTLISTENER_HPP_INCLUDED

#include <list>

namespace vik
{

class Event;
class EventSource;

// Interface enabling class to respond to Event signals
class EventListener
{
public:
	friend class EventSource;

	virtual ~EventListener();
	// return true if event is handled
	virtual bool onEvent(const Event& e){ return false; }
private:
	void addSource(EventSource* source);
	void removeSource(EventSource* source);
	std::list<EventSource*> sources;
};

} // end namespace vik

#endif // EVENTLISTENER_HPP_INCLUDED
