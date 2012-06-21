#include "viking/CombatScene.hpp"
#include "viking/PlayerFactory.hpp"
#include "viking/GameApp.hpp"

namespace vik
{

void CombatScene::onEnter()
{
	auto pf = std::make_shared<PlayerFactory>(HashedString("TestPlayer"), this);

	// give away ownership to the objectEngine
	objectEngine.addFactory(pf);
	
	// create one player for testing
	std::shared_ptr<GameObject> player = objectEngine.create(HashedString("TestPlayer"));

}

void CombatScene::onUpdate(GameTime& time)
{
	objectEngine.update(time);
}

void CombatScene::onLeave()
{
}

bool CombatScene::onEvent(const Event& e)
{
	return distributeEvent(e);
}

} // end namespace vik
