#include "viking/AnimatedSpriteSequence.hpp"

namespace vik
{

AnimatedSpriteSequence::AnimatedSpriteSequence(const irr::core::vector2di& startingTile, int length):
startingTile(startingTile),
length(length)
{
}

void AnimatedSpriteSequence::setLength(int length)
{
	this->length = length;
}

int AnimatedSpriteSequence::getLength() const
{
	return length;
}

void AnimatedSpriteSequence::setStartingTile(const irr::core::vector2di& startingTile)
{
	this->startingTile = startingTile;
}

const irr::core::vector2di& AnimatedSpriteSequence::getStartingTile() const
{
	return startingTile;
}


} // end namespace vik
