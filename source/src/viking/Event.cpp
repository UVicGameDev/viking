#include "viking/Event.hpp"
#include "viking/GameApp.hpp"
#include "viking/EventSource.hpp"

namespace vik
{

Event::Event(const std::shared_ptr<EventSource>& sender):
timeStamp(GameApp::getSingleton().getTimer()->getRealTime()),
sender(sender)
{
}

irr::u32 Event::getTimeStamp() const
{
	return timeStamp;
}

HashedString Event::getType() const
{
	return HashedString("Event");
}

const std::shared_ptr<EventSource>& Event::getSender() const
{
	return sender;
}

} // end namespace vik
