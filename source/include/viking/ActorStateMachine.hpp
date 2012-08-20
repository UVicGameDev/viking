#ifndef VIK_ACTORSTATEMACHINE_HPP_INCLUDED
#define VIK_ACTORSTATEMACHINE_HPP_INCLUDED

#include "viking/Serializable.hpp"
#include "viking/EventListener.hpp"
#include "viking/GameTime.hpp"
#include "viking/HashedString.hpp"
#include <memory>

namespace vik
{

class Actor;

class ActorStateMachine : public EventListener, public Serializable
{
public:
	ActorStateMachine(const std::weak_ptr<Actor>& context);

	void start();
	void update(GameTime& time);
	void stop();
	bool isRunning() const;

	void serializeAttributes(irr::io::IAttributes* out, irr::io::SAttributeReadWriteOptions* options=0) const override;
	void deserializeAttributes(irr::io::IAttributes* in, irr::io::SAttributeReadWriteOptions* options=0) override;

	virtual void switchToState(const HashedString& stateName) = 0;

protected:
	// called when start() is called
	virtual void onStart() = 0;
	// called when stop() is called
	virtual void onStop() = 0;
	// called when update() is called and the machine is running
	virtual void onUpdate(GameTime& time) = 0;

	std::weak_ptr<Actor>& getContext();
	const std::weak_ptr<Actor>& getContext() const;
private:
	std::weak_ptr<Actor> context;
	bool running;
};

} // end namespace vik

#endif // VIK_ACTORSTATEMACHINE_HPP_INCLUDED
