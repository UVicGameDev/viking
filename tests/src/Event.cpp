#include "viking/EventListener.hpp"
#include "viking/EventListener.cpp"
#include "viking/EventSource.hpp"
#include "viking/EventSource.cpp"
#include "viking/Event.hpp"
// #include "viking/Event.cpp" INTENTIONALLY OMITTED
#include "UnitTest.hpp"

class EventListenerTester : public vik::EventListener
{
public:
	EventListenerTester():
	eventCount(0)
	{
	}

	bool onEvent(const vik::Event& e)
	{
		eventCount++;
		return false;
	}

	int getEventCount() const
	{
		return eventCount;
	}

	void resetEventCount()
	{
		eventCount = 0;
	}
private:
	int eventCount;
};

int main()
{
{
	vik::EventSource s;
	auto l = std::make_shared<EventListenerTester>();

	// intentionally not using the vik::Event constructor
	// because it requires GameApp to be defined, which means
	// including a bazillion other files.
	vik::Event* bogusEvent = reinterpret_cast<vik::Event*>(new char[sizeof(vik::Event)]);

	// test no events
	l->resetEventCount();
	s.onEvent(*bogusEvent);
	TESTASSERT(l->getEventCount() == 0);

	l->resetEventCount();
	// test adding listener
	s.addListener(l);
	// test sending events
	s.onEvent(*bogusEvent);
	s.onEvent(*bogusEvent);
	s.onEvent(*bogusEvent);
	TESTASSERT(l->getEventCount() == 3);
	// test removing listener
	l->resetEventCount();
	s.removeListener(l);
	s.onEvent(*bogusEvent);
	TESTASSERT(l->getEventCount() == 0);

	// test listener being removed by being destroyed
	{
	auto l2 = std::make_shared<EventListenerTester>();
	s.addListener(l2);
	}
	s.onEvent(*bogusEvent);
}
	generateReport();
}
