#include "viking/GameObjectEngineActorQuery.hpp"
#include "viking/GameObjectEngine.hpp"
#include "viking/Actor.hpp"

namespace vik
{

GameObjectEngineActorQuery::GameObjectEngineActorQuery(GameObjectEngine* engine):
it(engine)
{
}

std::vector<std::shared_ptr<Actor>> GameObjectEngineActorQuery::getActors()
{
	std::vector<std::shared_ptr<Actor>> actorList;
	it.reset();
	while (it.hasNext())
	{
		std::shared_ptr<GameObject> curr = it.next();
		if (auto act = std::dynamic_pointer_cast<Actor>(curr))
		{
			actorList.push_back(act);
		}
	}
	return actorList;
}

} // end namespace vik
