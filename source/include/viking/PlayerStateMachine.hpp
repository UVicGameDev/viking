#ifndef VIK_PLAYERSTATEMACHINE_HPP_INCLUDED
#define VIK_PLAYERSTATEMACHINE_HPP_INCLUDED

#include "viking/ActorStateMachine.hpp"
#include "viking/ControlScheme.hpp"
#include "viking/PlayerIdleState.hpp"
#include "viking/PlayerMobileState.hpp"
#include "viking/PlayerAttackingState.hpp"

namespace vik
{

class PlayerStateMachine : public ActorStateMachine
{
public:
	PlayerStateMachine(const std::weak_ptr<Actor>& context, const HashedString& initialState, const ControlScheme& controlScheme);
	void initStates();
private:
	ControlScheme controlScheme;
};

} // end namespace vik

#endif // VIK_PLAYERSTATEMACHINE_HPP_INCLUDED
