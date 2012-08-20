#ifndef VIK_GAME_OBJECT_ENGINE_ITERATOR_HPP_INCLUDED
#define VIK_GAME_OBJECT_ENGINE_ITERATOR_HPP_INCLUDED

#include "viking/GameObjectEngine.hpp"

namespace vik
{

class GameObjectEngineIterator
{
public:
	GameObjectEngineIterator(GameObjectEngine* engine);
	bool hasNext() const;
	void reset();
	std::shared_ptr<GameObject> next();
private:
	GameObjectEngine* engine;
	std::list<std::shared_ptr<GameObject>>::iterator it;
};

} // end namespace vik

#endif // VIK_GAME_OBJECT_ENGINE_ITERATOR_HPP_INCLUDED
