#ifndef ACTOR_HPP_INCLUDED
#define ACTOR_HPP_INCLUDED

#include "viking/GameObject.hpp"
#include "viking/AnimatedSprite.hpp"
#include "viking/Particle.hpp"
#include "viking/HashString.hpp"
#include "viking/Event.hpp"
#include "viking/EventListener.hpp"
#include <vector>
#include <utility>

namespace vik
{

class ActorState;

class Actor : public GameObject, public EventListener
{
public:
	Actor();
	~Actor();
	
	// sets the current state to the given state and enters it
	void startStateMachine(HashedString initialStateName);

	// Adds a state to the list of possible states.
	// Actor claims ownership of state, always.
	void addState(HashedString stateName, ActorState* state);

	// leaves the current state and enters the next state
	void switchToState(HashedString nextState);

	// updates the current state
	void update(GameTime& time);

	// Passes on events to the current state
	bool onEvent(const Event& e);

	Particle& getParticle();

	void setSprite(std::shared_ptr<AnimatedSprite>& sprite);
	std::shared_ptr<AnimatedSprite>& getSprite();
	const std::shared_ptr<AnimatedSprite>& getSprite() const;
private:
	ActorState* currentState;
	std::vector<std::pair<HashedString,ActorState*>> states;

	Particle particle;
	std::shared_ptr<AnimatedSprite> sprite;
};

} // end namespace vik

#endif // ACTOR_HPP_INCLUDED
