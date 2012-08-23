#ifndef VIK_ANIMATEDSPRITE_HPP_INCLUDED
#define VIK_ANIMATEDSPRITE_HPP_INCLUDED

#include <irrlicht/ITexture.h>
#include <irrlicht/vector3d.h>
#include <irrlicht/S3DVertex.h>
#include <irrlicht/ISceneNode.h>
#include <memory>
#include "viking/AnimatedSpriteData.hpp"
#include "viking/GameTime.hpp"

namespace vik
{

class AnimatedSprite : public irr::scene::ISceneNode
{
public:
	AnimatedSprite(const std::shared_ptr<AnimatedSpriteData>& spriteData, irr::scene::ISceneNode* parent, irr::scene::ISceneManager* mgr, irr::s32 id=-1);

	void update(GameTime& time);
	
	void play(HashedString animSequence, int frame=0);
	void stop(HashedString animSequence, int frame=0);

	// true if the animation is playing and hasn't stopped because of not looping
	bool getPlaying() const;

	void setLooping(bool loop);
	bool getLooping() const;

	void setAnchor(const irr::core::vector3df& anchor);
	const irr::core::vector3df& getAnchor() const;

 	const irr::core::dimension2df& getSize() const;
	void setSize(const irr::core::dimension2df& size);

	// flip texture
	void setFlipHorizontal(bool flipped);
	bool getFlipHorizontal() const;

	// flip texture
	void setFlipVertical(bool flipped);
	bool getFlipVertical() const;

	// inherited from ISceneNode
	void OnRegisterSceneNode() override;
	void render() override;
	const irr::core::aabbox3df& getBoundingBox() const override;
	irr::core::matrix4 getRelativeTransformation() const override;

	irr::u32 getMaterialCount() const override;
	irr::video::SMaterial& getMaterial(irr::u32 i) override;

	void serializeAttributes(irr::io::IAttributes* out, irr::io::SAttributeReadWriteOptions* options=0) const override;
	void deserializeAttributes(irr::io::IAttributes* in, irr::io::SAttributeReadWriteOptions* options=0) override;
	irr::scene::ISceneNode* clone(irr::scene::ISceneNode* newParent=0, irr::scene::ISceneManager* newManager=0) override;

private:
	void setTileIndex(int index);

	// animation related stuff
	const std::shared_ptr<AnimatedSpriteData> spriteData;
	bool playing;
	irr::u32 startTime;
	int startFrame;
	const AnimatedSpriteSequence* currentSequence;

	bool looping;

	irr::core::vector3df anchor;

	bool flipHorizontal;
	bool flipVertical;

	// scene node related stuff
	irr::core::dimension2df size;
	irr::core::aabbox3df boundingBox;
	irr::video::SMaterial material;
	/* Vertices are:
	2--1
	|\ |
	| \|
	3--0
	*/
	irr::video::S3DVertex vertices[4];
	irr::u16 indices[6];
};

} // end namespace vik

#endif // ANIMATEDSPRITE_HPP_INCLUDED
