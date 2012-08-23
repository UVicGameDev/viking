#ifndef VIK_ACTOR_HPP_INCLUDED
#define VIK_ACTOR_HPP_INCLUDED

#include "viking/GameObject.hpp"
#include "viking/AnimatedSprite.hpp"
#include "viking/Particle.hpp"
#include "viking/HashedString.hpp"
#include "viking/Event.hpp"
#include "viking/EventSource.hpp"
#include <memory>

namespace vik
{

class ActorStateMachine;

class Actor : public GameObject, public EventSource
{
public:
	Actor();

	// Actors do not need a state machine to operate
	// However, setting up a state machine is recommended...
	void setStateMachine(const std::shared_ptr<ActorStateMachine>& stateMachine);
	std::shared_ptr<ActorStateMachine>& getStateMachine();

	// starts all subsystems
	void start();

	// stops all subsystems
	void stop();

	// updates the current state
	void update(GameTime& time);

	// returns whether subsystems are running or not
	bool isRunning() const;

	// Passes on events to the state machine
	bool onEvent(const Event& e);

	Particle& getParticle();

	void setSprite(std::shared_ptr<AnimatedSprite>& sprite);

	std::shared_ptr<AnimatedSprite>& getSprite();
	const std::shared_ptr<AnimatedSprite>& getSprite() const;

	void serializeAttributes(irr::io::IAttributes* out, irr::io::SAttributeReadWriteOptions* options=0) const override;
	void deserializeAttributes(irr::io::IAttributes* in, irr::io::SAttributeReadWriteOptions* options=0) override;
private:
	std::shared_ptr<ActorStateMachine> stateMachine;
	bool running;

	Particle particle;
	std::shared_ptr<AnimatedSprite> sprite;
};

} // end namespace vik

#endif // VIK_ACTOR_HPP_INCLUDED
