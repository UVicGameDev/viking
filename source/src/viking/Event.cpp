#include "viking/Event.hpp"
#include "viking/GameApp.hpp"
#include "viking/EventSource.hpp"

namespace vik
{

Event::Event():
timeStamp(GameApp::getSingleton().getTimer()->getRealTime())
{
}

irr::u32 Event::getTimeStamp() const
{
	return timeStamp;
}

const std::shared_ptr<EventSource>& Event::getSender() const
{
	return sender;
}

void Event::setSender(const std::shared_ptr<EventSource>& sender) const
{
	this->sender = sender;
}

} // end namespace vik
