#ifndef VIK_ANIMATEDSPRITESEQUENCE_HPP_INCLUDED
#define VIK_ANIMATEDSPRITESEQUENCE_HPP_INCLUDED

#include "viking/HashedString.hpp"
#include <string>

namespace vik
{

class AnimatedSpriteSequence
{
public:
	AnimatedSpriteSequence(const std::string& name, int start, int length, int FPS);
	const std::string& getName() const;
	HashedString getHashedName() const;
	int getStartIndex() const;
	int getLength() const;
	int getFPS() const;
private:
	// name used to refer to this sequence
	std::string name;
	HashedString hashedName;
	// tile index at which this sequence starts
	int start;
	// number of tiles this sequence lasts
	int length;
	int FPS;
};

} // end namesapce vik

#endif // VIK_ANIMATEDSPRITESEQUENCE_HPP_INCLUDED
