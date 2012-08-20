#ifndef VIK_ACTORSTATE_HPP_INCLUDED
#define VIK_ACTORSTATE_HPP_INCLUDED

#include "viking/EventListener.hpp"
#include "viking/Actor.hpp"
#include <memory>

namespace vik
{

class GameTime;

// modifies state of Actors as a function of time and events.
class ActorState : public EventListener
{
public:
	ActorState(const std::weak_ptr<Actor>& context);
	virtual ~ActorState(){}

	// Called when the state is entered
	virtual void onEnter(){}
	// Called at each tick
	virtual void onUpdate(GameTime& time){}
	// Called when the state is switched or the object is destroyed
	virtual void onLeave(){}
protected:
	// returns reference to actor this state modifies
	std::weak_ptr<Actor> getContext();
private:
	std::weak_ptr<Actor> context;
};

} // end namespace vik

#endif // VIK_ACTORSTATE_HPP_INCLUDED
