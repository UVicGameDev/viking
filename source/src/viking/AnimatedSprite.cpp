#include "viking/AnimatedSprite.hpp"
#include "viking/GameApp.hpp"
#include <iostream>

using namespace irr;

namespace vik
{

// hard coded test for now
AnimatedSprite::AnimatedSprite()
{
	originNode = GameApp::getSingleton().getSceneManager()->addEmptySceneNode();

	video::ITexture* t = GameApp::getSingleton().getVideoDriver()->getTexture("../../../art/sketch1.png");

	spriteNode = GameApp::getSingleton().getSceneManager()->addBillboardSceneNode(
		originNode,
		core::dimension2df(t->getSize()),
		core::vector3df(0.0f, 0.0f, t->getSize().Height/2));

	spriteNode->setMaterialFlag(video::EMF_LIGHTING, false);
	spriteNode->setMaterialFlag(video::EMF_BILINEAR_FILTER, false);
	spriteNode->setMaterialType(video::EMT_TRANSPARENT_ALPHA_CHANNEL_REF);
	spriteNode->setMaterialTexture(0, t);
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
