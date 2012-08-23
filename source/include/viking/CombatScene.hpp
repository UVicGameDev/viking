#ifndef VIK_COMBATSCENE_HPP_INCLUDED
#define VIK_COMBATSCENE_HPP_INCLUDED

#include "viking/Scene.hpp"
#include "viking/GameObjectEngine.hpp"
#include "viking/AnimationEngine.hpp"
#include <memory>

namespace vik
{

class PlayerFactory;
class AIFactory;

class CombatScene : public Scene, public std::enable_shared_from_this<CombatScene>
{
public:
	CombatScene();
	~CombatScene();

	void onEnter();
	void onUpdate(GameTime& time);
	void onLeave();
	bool onEvent(const Event& e);
	void onRedraw();
private:
	void updateCamera();
	GameObjectEngine objectEngine;
	AnimationEngine animationEngine;
	PlayerFactory* playerFactory;
	AIFactory* aiFactory;
	irr::u32 timeOnLastEventReceived;
};

} // end namespace vik

#endif // VIK_COMBATSCENE_HPP_INCLUDED
