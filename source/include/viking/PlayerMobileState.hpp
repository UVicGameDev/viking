#ifndef PLAYERMOBILESTATE_HPP_INCLUDED
#define PLAYERMOBILESTATE_HPP_INCLUDED

#include "viking/ActorState.hpp"

namespace vik
{

class PlayerMobileState : public ActorState
{
public:
	PlayerMobileState(HashedString stateName, const std::weak_ptr<Actor>& context);

	void onEnter();
	void onUpdate(GameTime& time);
	void onLeave();
	bool onEvent(const Event& e);
};

} // end namespace vik

#endif // PLAYERMOBILESTATE_HPP_INCLUDED
