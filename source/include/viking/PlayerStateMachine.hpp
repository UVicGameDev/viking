#ifndef VIK_PLAYERSTATEMACHINE_HPP_INCLUDED
#define VIK_PLAYERSTATEMACHINE_HPP_INCLUDED

#include "viking/ActorStateMachine.hpp"
#include "viking/ControlScheme.hpp"
#include "viking/PlayerIdleState.hpp"
#include "viking/PlayerMobileState.hpp"

namespace vik
{

class PlayerStateMachine : public ActorStateMachine
{
public:
	PlayerStateMachine(const std::weak_ptr<Actor>& context, const ControlScheme& controlScheme);

	void onStart() override;
	void onStop() override;
	void onUpdate(GameTime& time) override;

	void switchToState(const HashedString& stateName) override;

	bool onEvent(const Event& e) override;
private:
	ControlScheme controlScheme;

	PlayerIdleState idleState;
	PlayerMobileState mobileState;

	ActorState* currentState;
};

} // end namespace vik

#endif // VIK_PLAYERSTATEMACHINE_HPP_INCLUDED
