#ifndef VIK_PLAYERFACTORYCONFIGURATION_HPP_INCLUDED
#define VIK_PLAYERFACTORYCONFIGURATION_HPP_INCLUDED

#include "viking/ControlScheme.hpp"
#include <string>

namespace vik
{

class PlayerFactoryConfiguration
{
public:
	PlayerFactoryConfiguration(
			const std::string& playerType,
			const ControlScheme& controlScheme):
	playerType(playerType),
	controlScheme(controlScheme)
	{
	}

	std::string playerType;
	ControlScheme controlScheme;
};

} // end namespace vik

#endif // VIK_PLAYERFACTORYCONFIGURATION_HPP_INCLUDED
