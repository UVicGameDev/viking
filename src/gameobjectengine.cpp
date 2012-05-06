#include "gameobjectengine.h"
#include "gameobject.h"

namespace vik
{

void GameObjectEngine::Update(u32 dt)
{
    for(std::size_t i = 0; i < children.size(); ++i)
    {
        children[i]->Update(dt);
    }
}

} // end namespace vik
