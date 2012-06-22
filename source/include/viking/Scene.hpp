#ifndef SCENE_HPP_INCLUDED
#define SCENE_HPP_INCLUDED

#include "viking/GameTime.hpp"
#include "viking/EventSource.hpp"
#include "viking/Event.hpp"

namespace vik
{

class Scene : public EventSource
{
public:
	virtual ~Scene(){}
	virtual void onEnter() = 0;
	virtual void onUpdate(GameTime& time) = 0;
	virtual void onLeave() = 0;
	virtual void onRedraw(){}
};

} // end namespace vik

#endif // SCENE_HPP_INCLUDED
