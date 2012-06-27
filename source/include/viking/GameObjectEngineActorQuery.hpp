#ifndef GAME_OBJECT_ENGINE_ACTOR_QUERY_HPP_INCLUDED
#define GAME_OBJECT_ENGINE_ACTOR_QUERY_HPP_INCLUDED

#include <vector>
#include <memory>
#include "viking/GameObjectEngineIterator.hpp"

namespace vik
{

class Actor;
class GameObjectEngine;

// Uses RTTI to find all Actors in the GameObjectEngine
class GameObjectEngineActorQuery
{
public:
	GameObjectEngineActorQuery(GameObjectEngine* engine);
	std::vector<std::shared_ptr<Actor>> getActors();
private:
	GameObjectEngineIterator it;
};

} // end namespace vik

#endif // GAME_OBJECT_ENGINE_ACTOR_QUERY_HPP_INCLUDED
