#include "viking/AnimatedSpriteSequence.hpp"

namespace vik
{

AnimatedSpriteSequence::AnimatedSpriteSequence(const std::string& name, irr::u32 start, irr::u32 length, irr::u32 FPS):
name(name),
hashedName(HashedString(name.c_str())),
start(start),
length(length),
FPS(FPS)
{
}

const std::string& AnimatedSpriteSequence::getName() const
{
	return name;
}

HashedString AnimatedSpriteSequence::getHashedName() const
{
	return hashedName;
}

irr::u32 AnimatedSpriteSequence::getStartIndex() const
{
	return start;
}

irr::u32 AnimatedSpriteSequence::getLength() const
{
	return length;
}

irr::u32 AnimatedSpriteSequence::getFPS() const
{
	return FPS;
}

} // end namespace vik
