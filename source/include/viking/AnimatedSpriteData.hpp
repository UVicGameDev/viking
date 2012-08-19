#ifndef VIK_ANIMATEDSPRITEDATA_HPP_INCLUDED
#define VIK_ANIMATEDSPRITEDATA_HPP_INCLUDED

#include <vector>
#include "viking/AnimatedSpriteSequence.hpp"
#include "viking/HashString.hpp"
#include <irrlicht/ITexture.h>
#include <irrlicht/dimension2d.h>

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
	void setWidth(int width);
	void setHeight(int height);

	int getWidth() const;
	int getHeight() const;
private:
	int width;
	int height;
	std::vector<AnimatedSpriteSequence> sequences;
	irr::video::ITexture* texture;
};

} // end namespace vik

#endif // VIK_ANIMATEDSPRITEDATA_HPP_INCLUDED
