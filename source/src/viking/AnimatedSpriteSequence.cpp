#include "viking/AnimatedSpriteSequence.hpp"

namespace vik
{

AnimatedSpriteSequence::AnimatedSpriteSequence(const std::string& name, int start, int length, int FPS):
name(name),
hashedName(hashString(name.c_str())),
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

int AnimatedSpriteSequence::getStartIndex() const
{
	return start;
}

int AnimatedSpriteSequence::getLength() const
{
	return length;
}

int AnimatedSpriteSequence::getFPS() const
{
	return FPS;
}

} // end namespace vik
