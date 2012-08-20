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
			AnimationEngine& animationEngine,
			ePlayerType playerType):
	factoryID(factoryID),
	playerEventSource(playerEventSource),
	animationEngine(animationEngine),
	playerType(playerType)
	{
	}

	HashedString factoryID;
	EventSource* playerEventSource;
	AnimationEngine& animationEngine;
	ePlayerType playerType;
};

} // end namespace vik

#endif // VIK_PLAYERFACTORYCREATIONPARAMS_HPP
