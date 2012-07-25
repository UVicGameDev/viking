#include "viking/EventSource.hpp"
#include "viking/Event.hpp"
#include <algorithm>
#include <cassert>
#include <iostream>

namespace vik
{

bool EventSource::onEvent(const Event& event)
{
	return distributeEvent(event);
}

bool EventSource::distributeEvent(const Event& event)
{
	bool handled = false;
	for (std::list<std::weak_ptr<EventListener>>::iterator it = listeners.begin(); it != listeners.end() && !handled; )
	{
		// remove listeners lazily if their reference count is 0
		if (std::shared_ptr<EventListener> p = it->lock())
		{
			handled = p->onEvent(event);
			++it;
		}
		else
		{
			auto next = it;
			++next;
			listeners.erase(it);
			it = next;
		}
	}
	return handled;
}

void EventSource::addListener(const std::weak_ptr<EventListener>& listener)
{
	listeners.push_back(listener);
}

void EventSource::removeListener(const std::weak_ptr<EventListener>& listener)
{
	assert(listener.lock());

	auto it = listeners.begin();
	while (it != listeners.end())
	{
		// check if they both are weak pointers to the same shared pointer
		if ((*it).lock() == listener.lock())
		{
			break;
		}
		++it;
	}
	assert(it != listeners.end());
	listeners.erase(it);
}

} // end namespace vik
