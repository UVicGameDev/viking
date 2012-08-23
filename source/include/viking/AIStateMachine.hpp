#ifndef VIK_AISTATEMACHINE_HPP_INCLUDED
#define VIK_AISTATEMACHINE_HPP_INCLUDED

#include "viking/ActorStateMachine.hpp"
#include "viking/AIIdleState.hpp"

namespace vik
{

class AIStateMachine : public ActorStateMachine
{
public:
	AIStateMachine(const std::weak_ptr<Actor>& context, const HashedString& initialState);

	void initStates();
};

} // end namespace vik

#endif // VIK_AISTATEMACHINE_HPP_INCLUDED
