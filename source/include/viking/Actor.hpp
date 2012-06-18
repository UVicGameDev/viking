#ifndef ACTOR_HPP_INCLUDED
#define ACTOR_HPP_INCLUDED

#include "viking/GameObject.hpp"
#include "viking/AnimatedSprite.hpp"
#include "viking/Particle.hpp"
#include "viking/HashedString.hpp"
#include "viking/Event.hpp"
#include "viking/EventListener.hpp"
#include <vector>

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
	void addState(ActorState* state);
	// leaves the current state and enters the next state
	void switchToState(HashedString nextState);

	// updates the current state
	void update(GameTime& time);

	// Passes on events to the current state
	bool onEvent(const Event& e);

	Particle& getParticle();
private:
	ActorState* currentState;
	std::vector<ActorState*> states;

	Particle particle;
	AnimatedSprite sprite;
};

} // end namespace vik

#endif // ACTOR_HPP_INCLUDED
