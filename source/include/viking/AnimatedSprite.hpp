#ifndef ANIMATEDSPRITE_HPP_INCLUDED
#define ANIMATEDSPRITE_HPP_INCLUDED

#include <irrlicht/ITexture.h>
#include <irrlicht/IBillboardSceneNode.h>
#include <irrlicht/vector3d.h>
#include "viking/AnimatedSpriteData.hpp"

namespace vik
{

class AnimatedSprite
{
public:
	AnimatedSprite(AnimatedSpriteData* spriteData);
	~AnimatedSprite();

	void setPosition(const irr::core::vector3df& pos);
	irr::core::vector3df getPosition() const;

	void play(HashedString animSequence);
	void stop(HashedString animSequence);
private:
	AnimatedSpriteData* spriteData;
	irr::scene::ISceneNode* originNode;
	irr::scene::IBillboardSceneNode* spriteNode;
};

} // end namespace vik

#endif // ANIMATEDSPRITE_HPP_INCLUDED
