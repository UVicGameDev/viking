#include "viking/GameTime.hpp"
#include <iostream>
#include <cassert>

namespace vik
{

GameTime::GameTime(irr::ITimer* timer):
timer(timer),
lastTime(0),
deltaTime(0)
{
}

void GameTime::setTimer(irr::ITimer* timer)
{
	this->timer = timer;
}

irr::u32 GameTime::getRealTime() const
{
	return timer->getRealTime();
}

irr::f32 GameTime::getSpeed() const
{
	return timer->getSpeed();
}

irr::u32 GameTime::getTime() const
{
	return timer->getTime();
}

irr::u32 GameTime::getLastTime() const
{
	return lastTime;
}

irr::u32 GameTime::getDeltaTimeMilliSeconds() const
{
	return deltaTime;
}

irr::f32 GameTime::getDeltaTimeSeconds() const
{
	return deltaTime/1000.0f;
}

bool GameTime::isStopped() const
{
	return timer->isStopped();
}

void GameTime::setSpeed(irr::f32 speed)
{
	timer->setSpeed(speed);
}

void GameTime::setTime(irr::u32 time)
{
	lastTime = timer->getTime();
	timer->setTime(time);
	deltaTime = timer->getTime() - lastTime;
}

void GameTime::start()
{
	timer->start();
}

void GameTime::stop()
{
	assert(!timer->isStopped());

	timer->stop();
	if (timer->isStopped())
	{
		lastTime = timer->getTime();
		deltaTime = 0;
	}
}

void GameTime::updateWithoutTick()
{
	preTickUpdate();
	postTickUpdate();
}

void GameTime::updateWithTick()
{
	preTickUpdate();
	timer->tick();
	postTickUpdate();
}

void GameTime::preTickUpdate()
{
	deltaTime = timer->getTime() - lastTime;
}

void GameTime::postTickUpdate()
{
	lastTime = getTime();
}

} // end namespace vik
