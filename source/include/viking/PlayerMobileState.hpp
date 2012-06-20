#ifndef PLAYERMOBILESTATE_HPP_INCLUDED
#define PLAYERMOBILESTATE_HPP_INCLUDED

#include "viking/ActorState.hpp"
#include "viking/ControlScheme.hpp"
#include "viking/PlayerMovementAnimator.hpp"

namespace vik
{

class PlayerMobileState : public ActorState
{
public:
	PlayerMobileState(const std::weak_ptr<Actor>& context, const ControlScheme& scheme);

	void onEnter();
	void onUpdate(GameTime& time);
	void onLeave();
	bool onEvent(const Event& e);
private:
	PlayerMovementAnimator movementAnimator;
};

} // end namespace vik

#endif // PLAYERMOBILESTATE_HPP_INCLUDED
