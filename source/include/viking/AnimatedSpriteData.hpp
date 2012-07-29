#ifndef ANIMATEDSPRITEDATA_HPP_INCLUDED
#define ANIMATEDSPRITEDATA_HPP_INCLUDED

#include <map>
#include <string>
#include "viking/AnimatedSpriteSequence.hpp"
#include "viking/HashString.hpp"

namespace vik
{

class AnimatedSpriteData
{
public:
	AnimatedSpriteData();
	~AnimatedSpriteData();

	bool loadFromFile(const std::string& fileRootName);
private:
	std::map<HashedString,AnimatedSpriteSequence*> sequences;
	irr::video::ITexture* texture;
};

} // end namespace vik

#endif // ANIMATEDSPRITEDATA_HPP_INCLUDED
