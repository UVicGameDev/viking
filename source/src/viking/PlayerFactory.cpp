#include "viking/PlayerFactory.hpp"
#include "viking/Actor.hpp"
#include "viking/EventSource.hpp"
#include "viking/ControlScheme.hpp"

#include "viking/PlayerIdleState.hpp"
#include "viking/PlayerMobileState.hpp"

namespace vik
{

PlayerFactory::PlayerFactory(HashedString factoryID, EventSource* playerEventSource):
GameObjectFactory(factoryID),
playerEventSource(playerEventSource)
{
}

std::shared_ptr<GameObject> PlayerFactory::create()
{
	std::shared_ptr<Actor> player = std::make_shared<Actor>();

	playerEventSource->addListener(player);

	PlayerIdleState* idleState = new PlayerIdleState(player, ControlScheme());
	PlayerMobileState* mobileState = new PlayerMobileState(player, ControlScheme());

	player->addState(HashedString("Idle"), idleState);
	player->addState(HashedString("Mobile"), mobileState);

	player->startStateMachine(HashedString("Idle"));

	return player;
}

} // end namespace vik
