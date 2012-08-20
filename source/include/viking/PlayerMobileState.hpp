#ifndef VIK_PLAYERMOBILESTATE_HPP_INCLUDED
#define VIK_PLAYERMOBILESTATE_HPP_INCLUDED

#include "viking/ActorState.hpp"
#include "viking/ControlScheme.hpp"

namespace vik
{

class PlayerMobileState : public ActorState
{
public:
	PlayerMobileState(const std::weak_ptr<Actor>& context, ControlScheme& scheme);

	void onEnter();
	void onUpdate(GameTime& time);
	void onLeave();

	bool onEvent(const Event& e);
private:
	ControlScheme& scheme;
};

} // end namespace vik

#endif // VIK_PLAYERMOBILESTATE_HPP_INCLUDED
