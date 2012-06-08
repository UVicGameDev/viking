#include "viking/EventListener.hpp"
#include "viking/EventSource.hpp"
#include <algorithm>
#include <cassert>
#include <iostream>

namespace vik
{

EventListener::~EventListener()
{
	std::cout << "EventListener::~EventListener(this =" << this << ")" << std::endl;
	std::cout << "Number of sources at death: " << sources.size() << std::endl;
	for (std::list<EventSource*>::iterator it = sources.begin(); it != sources.end(); ++it)
	{
		(*it)->printListeners();
		(*it)->removeListener(this);
	}
}

void EventListener::addSource(EventSource* source)
{
	sources.push_back(source);
}

void EventListener::removeSource(EventSource* source)
{
	std::cout << "EventListener::removeSource(" << source << ")" << std::endl;
	source->printListeners();
	std::list<EventSource*>::iterator it = std::find(sources.begin(), sources.end(), source);
	assert(it != sources.end());

	std::cout << "sources.erase(" << *it << ")" << std::endl;
	sources.erase(it);
	source->printListeners();
}

} // end namespace vik
