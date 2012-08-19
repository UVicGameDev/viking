#ifndef COMBATSCENE_HPP_INCLUDED
#define COMBATSCENE_HPP_INCLUDED

#include "viking/Scene.hpp"
#include "viking/GameObjectEngine.hpp"
#include "viking/AnimationEngine.hpp"

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
	void updateCamera();
	GameObjectEngine objectEngine;
	AnimationEngine animationEngine;
};

} // end namespace vik

#endif // COMBATSCENE_HPP_INCLUDED
