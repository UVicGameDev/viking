#ifndef VIK_TEAMPROPERTIES_HPP_INCLUDED
#define VIK_TEAMPROPERTIES_HPP_INCLUDED

#include <string>
#include "viking/HashedString.hpp"

namespace vik
{

class TeamProperties
{
public:
	TeamProperties(int teamID, const std::string& teamName="NoName");

	void setTeamID(int teamID);
	int getTeamID() const;

	// Do not use the name to identify the team. Use the ID.
	void setTeamName(const std::string& teamName);
	const std::string& getTeamName() const;
private:
	int teamID;
	std::string teamName;
};

} // end namespace vik

#endif // VIK_TEAMPROPERTIES_HPP_INCLUDED
