#ifndef GAMETIME_HPP_INCLUDED
#define GAMETIME_HPP_INCLUDED

#include <irrlicht/ITimer.h>

namespace vik
{

class GameTime
{
public:
	// note: Making any calls to GameTime when the timer is null is undefined behaviour.
	GameTime(irr::ITimer* timer = 0);
	void setTimer(irr::ITimer* timer);

	// current time in milliseconds of system
	irr::u32 getRealTime() const;
	// get virtual time of application
	irr::u32 getTime() const;
	// get virtual time of last tick
	irr::u32 getLastTime() const;

	// get difference in virtual time from current to last tick
	irr::u32 getDeltaTimeMilliSeconds() const;
	irr::f32 getDeltaTimeSeconds() const;

	// current speed of time relative to system time flow
	irr::f32 getSpeed() const;
	// set speed of virtual timer relative to system time flow
	void setSpeed(irr::f32 speed);
	// true if the virtual timer is stopped
	bool isStopped() const;
	// manually re-arrange the virtual timer to a different time
	void setTime(irr::u32 time);

	// resumes and pauses the virtual timer
	// behaves like a stack: each call of stop must be matched by a start, otherwise it will not restart.
	void start();
	void stop();

	// updates virtual time based on real time
	// wrapped clock may or may not be ticked with this update
	// this accomodates the use case where an irrlicht clock is
	// being ticked by something else, but you want to wrap it
	// to get delta time information.
	void updateWithTick();
	void updateWithoutTick();
private:
	void preTickUpdate();
	void postTickUpdate();

	irr::ITimer* timer;

	// virtual timer's last tick time.
	irr::u32 lastTime;
	// difference between virtual last and current time
	irr::u32 deltaTime;
};

} // end namespace vik

#endif // GAMETIME_HPP_INCLUDED
