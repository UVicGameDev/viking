#include "viking/AnimatedSpriteData.hpp"
#include <algorithm>

namespace vik
{

AnimatedSpriteData::AnimatedSpriteData(irr::video::ITexture* tex):
width(0),
height(0),
texture(tex)
{
}

void AnimatedSpriteData::addSequence(const AnimatedSpriteSequence& seq)
{
	// insert in sorted order by hashedName
	auto it = std::find_if(sequences.begin(), sequences.end(),
		[seq](AnimatedSpriteSequence& other)
		{
			return other.getHashedName() >= seq.getHashedName();
		});

	sequences.insert(it, seq);
}

const AnimatedSpriteSequence* AnimatedSpriteData::getSequence(HashedString name) const
{
	// binary search
	size_t lower = 0, upper = sequences.size();

	while (lower != upper)
	{
		int i = (lower + upper - 1) / 2;
		if (sequences[i].getHashedName() == name)
		{
			return &sequences[i];
		}
		else if (sequences[i].getHashedName() < name)
		{
			lower = i + 1;
		}
		else
		{
			upper = i;
		}
	}

	return NULL;
}

irr::video::ITexture* AnimatedSpriteData::getTexture()
{
	return texture;
}

const irr::video::ITexture* AnimatedSpriteData::getTexture() const
{
	return texture;
}

void AnimatedSpriteData::setWidth(irr::u32 width)
{
	this->width = width;
}

void AnimatedSpriteData::setHeight(irr::u32 height)
{
	this->height = height;
}

irr::u32 AnimatedSpriteData::getWidth() const
{
	return width;
}

irr::u32 AnimatedSpriteData::getHeight() const
{
	return height;
}

} // end namespace vik
