#ifndef VIK_PLAYERATTACKINGSTATE_HPP_INCLUDED
#define VIK_PLAYERATTACKINGSTATE_HPP_INCLUDED

#include "viking/ActorState.hpp"
#include "viking/ControlScheme.hpp"

namespace vik
{

class PlayerAttackingState : public ActorState
{
public:
	PlayerAttackingState(const std::weak_ptr<Actor>& context, ControlScheme& scheme);

	void onEnter();
	void onUpdate(GameTime& time);
	void onLeave();
	bool onEvent(const Event& e);
private:
	ControlScheme& scheme;

};

} // end namespace vik

#endif // VIK_PLAYERATTACKINGSTATE_HPP_INCLUDED
