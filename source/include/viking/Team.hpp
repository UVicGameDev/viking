#ifndef VIK_TEAM_HPP_INCLUDED
#define VIK_TEAM_HPP_INCLUDED

#include "viking/TeamProperties.hpp"
#include <map>

namespace vik
{

class TeamMembership;

class Team
{
public:
	Team(const TeamProperties& properties);
	~Team();

	const TeamProperties& getProperties() const;

	const TeamMembership* requestMembership();
private:
	TeamProperties properties;
	// id to give to the next member to register
	int nextMemberID;
	std::map<int, TeamMembership*> members;
};

} // end namespace vik

#endif // VIK_TEAM_HPP_INCLUDED
