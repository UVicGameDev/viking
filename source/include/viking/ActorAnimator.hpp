#ifndef ACTOR_ANIMATOR_HPP
#define ACTOR_ANIMATOR_HPP

#include "viking/GameTime.hpp"

namespace vik
{

class Actor;

// animator for affecting the position of actors externally
class ActorAnimator
{
public:
	ActorAnimator(Actor& target):
	target(target)
	{
	}
	virtual ~ActorAnimator(){}

	virtual void update(GameTime& time){}
protected:
	Actor& target;
};

} // end namespace vik

#endif // ACTOR_ANIMATOR_HPP
