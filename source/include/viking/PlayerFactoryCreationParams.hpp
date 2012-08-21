#ifndef VIK_PLAYERFACTORYCREATIONPARAMS_HPP
#define VIK_PLAYERFACTORYCREATIONPARAMS_HPP

namespace vik
{

class EventSource;
class AnimationEngine;

enum ePlayerType
{
	EPT_ARTSIE
};

struct PlayerFactoryCreationParams
{
	PlayerFactoryCreationParams(
			HashedString factoryID,
			EventSource* playerEventSource,
			AnimationEngine& animationEngine):
	factoryID(factoryID),
	playerEventSource(playerEventSource),
	animationEngine(animationEngine)
	{
	}

	HashedString factoryID;
	EventSource* playerEventSource;
	AnimationEngine& animationEngine;
};

} // end namespace vik

#endif // VIK_PLAYERFACTORYCREATIONPARAMS_HPP
