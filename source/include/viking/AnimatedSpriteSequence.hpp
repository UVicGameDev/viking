#ifndef VIK_ANIMATEDSPRITESEQUENCE_HPP_INCLUDED
#define VIK_ANIMATEDSPRITESEQUENCE_HPP_INCLUDED

#include "viking/HashedString.hpp"
#include <string>
#include <irrlicht/irrTypes.h>

namespace vik
{

class AnimatedSpriteSequence
{
public:
	AnimatedSpriteSequence(const std::string& name, irr::u32 start, irr::u32 length, irr::u32 FPS);
	const std::string& getName() const;
	HashedString getHashedName() const;
	irr::u32 getStartIndex() const;
	irr::u32 getLength() const;
	irr::u32 getFPS() const;
private:
	// name used to refer to this sequence
	std::string name;
	HashedString hashedName;
	// tile index at which this sequence starts
	irr::u32 start;
	// number of tiles this sequence lasts
	irr::u32 length;
	irr::u32 FPS;
};

} // end namesapce vik

#endif // VIK_ANIMATEDSPRITESEQUENCE_HPP_INCLUDED
