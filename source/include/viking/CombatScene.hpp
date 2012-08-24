#ifndef VIK_COMBATSCENE_HPP_INCLUDED
#define VIK_COMBATSCENE_HPP_INCLUDED

#include "viking/Scene.hpp"
#include "viking/GameObjectEngine.hpp"
#include "viking/AnimationEngine.hpp"
#include <memory>
#include <vector>

namespace vik
{

class PlayerFactory;
class AIFactory;
class DamageZoneCreationEvent;
class Team;

class CombatScene : public Scene
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
	void handleDamageZoneCreation(const DamageZoneCreationEvent& e);
	void updateCamera();
	GameObjectEngine objectEngine;
	AnimationEngine animationEngine;
	PlayerFactory* playerFactory;
	AIFactory* aiFactory;

	Team* playerTeam;
	Team* enemyTeam;

	std::vector<irr::core::aabbox3df> renderBoxOnceDebugQueue;
};

} // end namespace vik

#endif // VIK_COMBATSCENE_HPP_INCLUDED
