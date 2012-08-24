#ifndef VIK_AISTATEMACHINE_HPP_INCLUDED
#define VIK_AISTATEMACHINE_HPP_INCLUDED

#include "viking/ActorStateMachine.hpp"
#include "viking/AIIdleState.hpp"

namespace vik
{

class TeamMembership;

class AIStateMachine : public ActorStateMachine
{
public:
	AIStateMachine(const std::weak_ptr<Actor>& context, const HashedString& initialState);

	void initStates();

	void setTeamMembership(const TeamMembership* teamMembership);
private:
	bool onPreUpstreamEvent(const Event& e) override;
	bool onPreDownstreamEvent(const Event& e) override;

	const TeamMembership* teamMembership;
};

} // end namespace vik

#endif // VIK_AISTATEMACHINE_HPP_INCLUDED
