#ifndef VIK_ANIMATEDSPRITEDATA_HPP_INCLUDED
#define VIK_ANIMATEDSPRITEDATA_HPP_INCLUDED

#include <vector>
#include "viking/AnimatedSpriteSequence.hpp"
#include "viking/HashedString.hpp"
#include <irrlicht/ITexture.h>
#include <irrlicht/dimension2d.h>
#include <irrlicht/irrTypes.h>

namespace vik
{

class AnimatedSpriteData
{
public:
	AnimatedSpriteData(irr::video::ITexture* tex);
	void addSequence(const AnimatedSpriteSequence& seq);
	const AnimatedSpriteSequence* getSequence(HashedString name) const;

	irr::video::ITexture* getTexture();
	const irr::video::ITexture* getTexture() const;

	// in number of tiles
	void setWidth(irr::u32 width);
	void setHeight(irr::u32 height);

	irr::u32 getWidth() const;
	irr::u32 getHeight() const;
private:
	irr::u32 width;
	irr::u32 height;
	std::vector<AnimatedSpriteSequence> sequences;
	irr::video::ITexture* texture;
};

} // end namespace vik

#endif // VIK_ANIMATEDSPRITEDATA_HPP_INCLUDED
