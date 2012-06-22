#ifndef COMBATSCENE_HPP_INCLUDED
#define COMBATSCENE_HPP_INCLUDED

#include "viking/Scene.hpp"
#include "viking/GameObjectEngine.hpp"

namespace vik
{

class CombatScene : public Scene
{
public:
	void onEnter();
	void onUpdate(GameTime& time);
	void onLeave();
	bool onEvent(const Event& e);
	void onRedraw();
private:
	GameObjectEngine objectEngine;
};

} // end namespace vik

#endif // COMBATSCENE_HPP_INCLUDED
