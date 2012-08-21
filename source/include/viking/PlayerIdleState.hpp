#ifndef VIK_PLAYERIDLESTATE_HPP_INCLUDED
#define VIK_PLAYERIDLESTATE_HPP_INCLUDED

#include "viking/ActorState.hpp"
#include "viking/ControlScheme.hpp"

namespace vik
{

// state a player is in when they are not moving (hence idle)
class PlayerIdleState : public ActorState
{
public:
	PlayerIdleState(const std::weak_ptr<Actor>& context, ControlScheme& scheme);
	void onEnter();
	void onUpdate(GameTime& time);
	void onLeave();
	bool onEvent(const Event& e);
private:
	ControlScheme& scheme;
};

} // end namespace vik

#endif // VIK_PLAYERIDLESTATE_HPP_INCLUDED
