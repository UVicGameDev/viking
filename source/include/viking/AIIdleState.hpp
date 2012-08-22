#ifndef VIK_AIIDLESTATE_HPP_INCLUDED
#define VIK_AIIDLESTATE_HPP_INCLUDED

#include "viking/ActorState.hpp"

namespace vik
{

class AIIdleState : public ActorState
{
public:
	AIIdleState(const std::weak_ptr<Actor>& context);
	void onEnter() override;
};

} // end namespace vik

#endif // VIK_AIIDLESTATE_HPP_INCLUDED
