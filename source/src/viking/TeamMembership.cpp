#include "viking/TeamMembership.hpp"
#include "viking/TeamProperties.hpp"

namespace vik
{

TeamMembership::TeamMembership(int membershipID, const Team* team):
membershipID(membershipID),
team(team)
{
}

int TeamMembership::getMembershipID() const
{
	return membershipID;
}

const Team* TeamMembership::getTeam() const
{
	return team;
}

} // end namespace vik
