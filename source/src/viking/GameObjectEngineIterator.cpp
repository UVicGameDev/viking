#include "viking/GameObjectEngineIterator.hpp"

namespace vik
{

GameObjectEngineIterator::GameObjectEngineIterator(GameObjectEngine* engine):
engine(engine)
{
	reset();
}

bool GameObjectEngineIterator::hasNext() const
{
	return it != engine->objectList.end();
}

void GameObjectEngineIterator::reset()
{
	it = engine->objectList.begin();
}

std::shared_ptr<GameObject> GameObjectEngineIterator::next()
{
	auto last = it;
	++it;
	return *last;
}

} // end namespace vik
