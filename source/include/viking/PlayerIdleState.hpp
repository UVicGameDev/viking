#ifndef PLAYERIDLESTATE_HPP_INCLUDED
#define PLAYERIDLESTATE_HPP_INCLUDED

#include "viking/ActorState.hpp"
#include "viking/ControlScheme.hpp"

namespace vik
{

// state a player is in when they are not moving (hence idle)
class PlayerIdleState : public ActorState
{
public:
	PlayerIdleState(HashedString stateName, const std::weak_ptr<Actor>& context, const ControlScheme& scheme);

	void onEnter();
	void onUpdate(GameTime& time);
	void onLeave();
	bool onEvent(const Event& e);
private:
	ControlScheme scheme;
};

} // end namespace vik

#endif // PLAYERIDLESTATE_HPP_INCLUDED
