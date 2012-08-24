#ifndef VIK_GAMEOBJECT_HPP_INCLUDED
#define VIK_GAMEOBJECT_HPP_INCLUDED

#include "viking/GameTime.hpp"
#include "viking/Serializable.hpp"

namespace vik
{

// Base class for all GameObjects in the game.
// GameObjects have a state that is updated as a function of time with update()
// GameObjects are possible to serialize/deserialize. (Inherited from Serializable)

// On inheritance: Try to only subclass this class once. Twice is the absolute maximum, and multiple inheritance of this class is not allowed.
class GameObject : public Serializable
{
public:
	virtual ~GameObject(){}

	// update state as a function of delta time
	virtual void update(GameTime& time) = 0;
};

} // end namespace vik

#endif // VIK_GAMEOBJECT_HPP_INCLUDED
