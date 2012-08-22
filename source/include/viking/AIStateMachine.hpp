#ifndef VIK_AISTATEMACHINE_HPP_INCLUDED
#define VIK_AISTATEMACHINE_HPP_INCLUDED

#include "viking/ActorStateMachine.hpp"
#include "viking/AIIdleState.hpp"

namespace vik
{

class AIStateMachine : public ActorStateMachine
{
public:
	AIStateMachine(const std::weak_ptr<Actor>& context);

	void onStart() override;
	void onStop() override;
	void onUpdate(GameTime& time) override;

	void switchToState(const HashedString& stateName) override;

	bool onEvent(const Event& e) override;
private:
	AIIdleState idleState;

	ActorState* currentState;
};

} // end namespace vik

#endif // VIK_AISTATEMACHINE_HPP_INCLUDED
