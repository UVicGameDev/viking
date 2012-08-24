#ifndef VIK_TEAMMEMBERSHIP_HPP_INCLUDED
#define VIK_TEAMMEMBERSHIP_HPP_INCLUDED

namespace vik
{

class Team;

class TeamMembership
{
public:
	TeamMembership(int membershipID, const Team* team);

	int getMembershipID() const;
	const Team* getTeam() const;
private:
	int membershipID;
	const Team* team;
};

} // end namespace vik

#endif // VIK_TEAMMEMBERSHIP_HPP_INCLUDED
