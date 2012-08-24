#include "viking/Team.hpp"
#include "viking/TeamMembership.hpp"

#include <cassert>

namespace vik
{

Team::Team(const TeamProperties& properties):
properties(properties),
nextMemberID(0)
{
}

Team::~Team()
{
	for (auto it : members)
	{
		delete it.second;
	}
}

const TeamProperties& Team::getProperties() const
{
	return properties;
}

const TeamMembership* Team::requestMembership()
{
	TeamMembership* membership = new TeamMembership(nextMemberID, this);

	assert(members.find(nextMemberID) == members.end());

	members[nextMemberID] = membership;

	++nextMemberID;

	return membership;
}

} // end namespace vik
