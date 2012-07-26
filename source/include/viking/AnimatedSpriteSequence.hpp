#ifndef ANIMATEDSPRITESEQUENCE_HPP_INCLUDED
#define ANIMATEDSPRITESEQUENCE_HPP_INCLUDED

#include <irrlicht/vector2d.h>

namespace vik
{

class AnimatedSpriteSequence
{
public:
	AnimatedSpriteSequence(const irr::core::vector2di& startingTile = irr::core::vector2di(), int length = 0);

	void setLength(int length);
	int getLength() const;
	void setStartingTile(const irr::core::vector2di& startingTile);
	const irr::core::vector2di& getStartingTile() const;
private:
	irr::core::vector2di startingTile;
	int length;
};

} // end namesapce vik

#endif // ANIMATEDSPRITESEQUENCE_HPP_INCLUDED
