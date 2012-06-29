#include "viking/AnimatedSprite.hpp"
#include "viking/GameApp.hpp"
#include <iostream>

using namespace irr;

namespace vik
{

// hard coded test for now
AnimatedSprite::AnimatedSprite(video::ITexture* spriteTex)
{
	originNode = GameApp::getSingleton().getSceneManager()->addEmptySceneNode();

	spriteNode = GameApp::getSingleton().getSceneManager()->addBillboardSceneNode(
		originNode,
		core::dimension2df(spriteTex->getSize()),
		core::vector3df(0.0f, 0.0f, spriteTex->getSize().Height/2));

	spriteNode->setMaterialFlag(video::EMF_LIGHTING, false);
	spriteNode->setMaterialFlag(video::EMF_BILINEAR_FILTER, false);
	spriteNode->setMaterialType(video::EMT_TRANSPARENT_ALPHA_CHANNEL_REF);
	spriteNode->setMaterialTexture(0, spriteTex);
}

AnimatedSprite::~AnimatedSprite()
{
	originNode->removeAll();
}

void AnimatedSprite::setPosition(const core::vector3df& pos)
{
	originNode->setPosition(pos);
}

core::vector3df AnimatedSprite::getPosition() const
{
	return originNode->getPosition();
}

} // end namespace vik
