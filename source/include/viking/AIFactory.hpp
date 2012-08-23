#ifndef VIK_AIFACTORY_HPP_INCLUDED
#define VIK_AIFACTORY_HPP_INCLUDED

#include "viking/ActorFactory.hpp"

namespace vik
{

class EventSource;
class AnimationEngine;

class AIFactory : public ActorFactory
{
public:
	AIFactory(HashedString factoryID, EventSource* aiEventSource, AnimationEngine& animationEngine);

	void setConfiguration(const std::string& aiName);

	std::shared_ptr<Actor> create() override;
private:
	EventSource* aiEventSource;
	AnimationEngine& animationEngine;
};

} // end namespace vik

#endif // VIK_AIFACTORY_HPP_INCLUDED
