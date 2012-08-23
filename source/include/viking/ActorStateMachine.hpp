#ifndef VIK_ACTORSTATEMACHINE_HPP_INCLUDED
#define VIK_ACTORSTATEMACHINE_HPP_INCLUDED

#include "viking/Serializable.hpp"
#include "viking/EventSource.hpp"
#include "viking/GameTime.hpp"
#include "viking/HashedString.hpp"
#include <memory>
#include <map>

namespace vik
{

class Actor;
class ActorState;

class ActorStateMachine : public EventSource, public Serializable
{
public:
	ActorStateMachine(const std::weak_ptr<Actor>& context, const HashedString& initialState);
	~ActorStateMachine() override;

	void start();
	void update(GameTime& time);
	void stop();
	bool isRunning() const;

	bool onEvent(const Event& e) override final;

	// takes unique strong ownership of all states added
	// BEWARE: You may not add states to the machine in the derived constructor because the state machine must be fully constructed before. You must add the states after the machine is constructed through your own means.
	void addState(const HashedString& stateName, const std::shared_ptr<ActorState>& state);
	void switchToState(const HashedString& stateName);
	std::shared_ptr<ActorState>& getCurrentState();

	void serializeAttributes(irr::io::IAttributes* out, irr::io::SAttributeReadWriteOptions* options=0) const override;
	void deserializeAttributes(irr::io::IAttributes* in, irr::io::SAttributeReadWriteOptions* options=0) override;

protected:
	// hooks for derived classes
	
	// just after initialization
	virtual void onStart(){}
	// just before deinitialization
	virtual void onStop(){}
	// just before update
	virtual void onPreUpdate(GameTime& time){}
	// just after update
	virtual void onPostUpdate(GameTime& time){}
	// just before receiving an event from the context
	virtual bool onPreDownstreamEvent(const Event& e){ return false; }
	// just before receiving an event from current state
	virtual bool onPreUpstreamEvent(const Event& e){ return false; }

	std::weak_ptr<Actor>& getContext();
	const std::weak_ptr<Actor>& getContext() const;
private:
	std::weak_ptr<Actor> context;
	bool running;

	const HashedString initialState;
	std::map<HashedString,std::shared_ptr<ActorState>> states;
	std::shared_ptr<ActorState> currentState;
};

} // end namespace vik

#endif // VIK_ACTORSTATEMACHINE_HPP_INCLUDED
