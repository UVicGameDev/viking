#include "viking/TeamProperties.hpp"

namespace vik
{

TeamProperties::TeamProperties(int teamID, const std::string& teamName):
teamID(teamID),
teamName(teamName)
{
}

void TeamProperties::setTeamID(int teamID)
{
	this->teamID = teamID;
}

int TeamProperties::getTeamID() const
{
	return teamID;
}

void TeamProperties::setTeamName(const std::string& teamName)
{
	this->teamName = teamName;
}

const std::string& TeamProperties::getTeamName() const
{
	return teamName;
}

} // end namespace vik
