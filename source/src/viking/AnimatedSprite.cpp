#include "viking/AnimatedSprite.hpp"
#include "viking/GameApp.hpp"
#include <iostream>
#include <cmath>
#include <cassert>
#include <algorithm>
#include "viking/IrrlichtStream.hpp"

using namespace irr;

namespace vik
{

// hard coded test for now
AnimatedSprite::AnimatedSprite(const std::shared_ptr<AnimatedSpriteData>& spriteData, scene::ISceneNode* parent, irr::scene::ISceneManager* mgr, irr::s32 id):
scene::ISceneNode(parent, mgr, id),
spriteData(spriteData),
playing(false),
startTime(0),
startFrame(0),
currentSequence(0),
looping(false),
flipHorizontal(false),
flipVertical(false)
{
	core::dimension2du orig = spriteData->getTexture()->getOriginalSize();
	setSize(core::dimension2df(orig.Width / spriteData->getWidth(), size.Height = orig.Height / spriteData->getHeight()));

	// initialize vertices
	material.Lighting = false;
	material.setFlag(video::EMF_BILINEAR_FILTER, false);
	material.MaterialType = video::EMT_TRANSPARENT_ALPHA_CHANNEL_REF;
	material.setTexture(0, spriteData->getTexture());

	indices[0] = 0;
	indices[1] = 2;
	indices[2] = 1;
	indices[3] = 0;
	indices[4] = 3;
	indices[5] = 2;

	vertices[0].TCoords.set(1.0f, 1.0f);
	vertices[1].TCoords.set(1.0f, 0.0f);
	vertices[2].TCoords.set(0.0f, 0.0f);
	vertices[3].TCoords.set(0.0f, 1.0f);

	for (int i = 0; i < 4; i++)
	{
		vertices[i].Color.set(255,255,255,255);
	}
}

void AnimatedSprite::update(GameTime& time)
{
	if (playing)
	{
		if (currentSequence->getFPS() > 0 && currentSequence->getLength() > 0)
		{
			u32 currentTime = time.getTime();
			u32 deltaTime = currentTime - startTime;
			u32 currentFrame = deltaTime*currentSequence->getFPS()/1000.0;
			currentFrame += startFrame;

			// if looping is disabled, it will stop animating at the last frame.
			if (!looping && currentFrame >= currentSequence->getLength())
			{
				playing = false;
				return;
			}

			currentFrame %= currentSequence->getLength();
			setTileIndex(currentSequence->getStartIndex() + currentFrame);
		}
	}
}

void AnimatedSprite::play(HashedString animSequence, int frame)
{
	currentSequence = spriteData->getSequence(animSequence);
	assert(currentSequence);
	startTime = GameApp::getSingleton().getTimer()->getTime();
	startFrame = frame;
	playing = true;
	setTileIndex(currentSequence->getStartIndex() + frame);
}

void AnimatedSprite::stop(HashedString animSequence, int frame)
{
	currentSequence = spriteData->getSequence(animSequence);
	assert(currentSequence);
	startTime = GameApp::getSingleton().getTimer()->getTime();
	startFrame = frame;
	playing = false;
	setTileIndex(currentSequence->getStartIndex() + frame);
}

void AnimatedSprite::setTileIndex(int index)
{
	int width = spriteData->getWidth();
	int x = index % width;
	int y = (index - x) / width;
	float clipw = 1.0f / width;
	float cliph = 1.0f / spriteData->getHeight();

	vertices[0].TCoords.set(clipw * (x+1), cliph * (y+1));
	vertices[1].TCoords.set(clipw * (x+1), cliph * y);
	vertices[2].TCoords.set(clipw * x, cliph * y);
	vertices[3].TCoords.set(clipw * x, cliph * (y+1));

	/*
	std::cout << "Vertices: { " << std::endl
	<< vertices[0] << std::endl
	<< vertices[1] << std::endl
	<< vertices[2] << std::endl
	<< vertices[3] << std::endl
	<< " }" << std::endl;
	*/
}

void AnimatedSprite::OnRegisterSceneNode()
{
	if (IsVisible)
		SceneManager->registerNodeForRendering(this);

	scene::ISceneNode::OnRegisterSceneNode();
}

void AnimatedSprite::render()
{
	video::IVideoDriver* driver = SceneManager->getVideoDriver();
	scene::ICameraSceneNode* camera = SceneManager->getActiveCamera();

	if (!camera || !driver)
		return;

	// make billboard look to camera

	core::vector3df pos = getAbsolutePosition();
	
	core::vector3df campos = camera->getAbsolutePosition();
	core::vector3df target = camera->getTarget();
	core::vector3df up = camera->getUpVector();
	core::vector3df view = target - campos;
	view.normalize();

	core::vector3df horizontal = up.crossProduct(view);
	if ( horizontal.getLength() == 0 )
	{
		horizontal.set(up.Y,up.X,up.Z);
	}
	horizontal.normalize();
	horizontal *= 0.5f * size.Width;

	// pointing down!
	core::vector3df vertical = horizontal.crossProduct(view);
	vertical.normalize();
	vertical *= 0.5f * size.Height;

	view *= -1.0f;

	for (s32 i = 0; i < 4; ++i)
		vertices[i].Normal = view;

	/* Vertices are:
	2--1
	|\ |
	| \|
	3--0
	*/
	vertices[0].Pos = pos + horizontal + vertical;
	vertices[1].Pos = pos + horizontal - vertical;
	vertices[2].Pos = pos - horizontal - vertical;
	vertices[3].Pos = pos - horizontal + vertical;

	// Coordinates are swapped back into place after drawing
	if (flipHorizontal)
	{
		std::swap(vertices[0].TCoords, vertices[3].TCoords);
		std::swap(vertices[1].TCoords, vertices[2].TCoords);
	}

	if (flipVertical)
	{
		std::swap(vertices[0].TCoords, vertices[1].TCoords);
		std::swap(vertices[2].TCoords, vertices[3].TCoords);
	}

	// draw

	if (DebugDataVisible & scene::EDS_BBOX)
	{
		driver->setTransform(video::ETS_WORLD, AbsoluteTransformation);
		video::SMaterial m;
		m.Lighting = false;
		driver->setMaterial(m);
		driver->draw3DBox(boundingBox, video::SColor(0,208,195,152));
	}

	driver->setTransform(video::ETS_WORLD, core::IdentityMatrix);

	driver->setMaterial(material);

	driver->drawIndexedTriangleList(vertices, 4, indices, 2);

	// swap back coordinates after swapping them to draw the image flipped
	if (flipVertical)
	{
		std::swap(vertices[0].TCoords, vertices[1].TCoords);
		std::swap(vertices[2].TCoords, vertices[3].TCoords);
	}

	if (flipHorizontal)
	{
		std::swap(vertices[0].TCoords, vertices[3].TCoords);
		std::swap(vertices[1].TCoords, vertices[2].TCoords);
	}
}

const irr::core::aabbox3df& AnimatedSprite::getBoundingBox() const
{
	return boundingBox;
}

core::matrix4 AnimatedSprite::getRelativeTransformation() const
{
	core::matrix4 mat;
	mat.setRotationDegrees(RelativeRotation);
	mat.setTranslation(RelativeTranslation + (anchor/2));
	if (RelativeScale != core::vector3df(1.f,1.f,1.f))
	{
		core::matrix4 smat;
		smat.setScale(RelativeScale);
		mat *= smat;
	}

	return mat;
}

irr::u32 AnimatedSprite::getMaterialCount() const
{
	return 1;
}

irr::video::SMaterial& AnimatedSprite::getMaterial(irr::u32 i)
{
	return material;
}

void AnimatedSprite::serializeAttributes(io::IAttributes* out, io::SAttributeReadWriteOptions* options) const
{
	scene::ISceneNode::serializeAttributes(out, options);

	out->addFloat("Width", size.Width);
	out->addFloat("Height", size.Height);
}

void AnimatedSprite::deserializeAttributes(io::IAttributes* in, io::SAttributeReadWriteOptions* options)
{
	scene::ISceneNode::deserializeAttributes(in, options);

	size.Width = in->getAttributeAsFloat("Width");
	size.Height = in->getAttributeAsFloat("Height");
	setSize(size);
}

scene::ISceneNode* AnimatedSprite::clone(scene::ISceneNode* newParent, scene::ISceneManager* newManager)
{
	if (!newParent)
		newParent = Parent;
	if (!newManager)
		newManager = SceneManager;

	AnimatedSprite* ns = new AnimatedSprite(spriteData, newParent,
		newManager, ID);
	ns->setSize(size);
	ns->playing = playing;
	ns->startTime = startTime;
	ns->startFrame = startFrame;
	ns->currentSequence = currentSequence;

	ns->cloneMembers(this, newManager);
	ns->material = material;

	if ( newParent )
		ns->drop();

	return ns;
}

const irr::core::dimension2df& AnimatedSprite::getSize() const
{
	return size;
}

void AnimatedSprite::setSize(const irr::core::dimension2df& size)
{
	this->size = size;

	if (core::equals(size.Width, 0.0f))
		this->size.Width = 1.0f;

	if (core::equals(size.Height, 0.0f))
		this->size.Height = 1.0f;

	// copy and pasted this nonsense from CBillboardSceneNode
	// const f32 avg = (this->size.Width + this->size.Height)/6;
	boundingBox.MinEdge.set(-this->size.Width/2, -2.5f, -this->size.Height/2);
	boundingBox.MaxEdge.set(this->size.Width/2, 2.5f, this->size.Height/2);
	/*
	boundingBox.MinEdge.set(-avg,-avg,-avg);
	boundingBox.MaxEdge.set(avg,avg,avg);
	*/
}

void AnimatedSprite::setAnchor(const irr::core::vector3df& anchor)
{
	this->anchor = anchor;
}

const irr::core::vector3df& AnimatedSprite::getAnchor() const
{
	return anchor;
}

void AnimatedSprite::setFlipHorizontal(bool flipped)
{
	flipHorizontal = flipped;
}

bool AnimatedSprite::getFlipHorizontal() const
{
	return flipHorizontal;
}

void AnimatedSprite::setFlipVertical(bool flipped)
{
	flipVertical = flipped;
}

bool AnimatedSprite::getFlipVertical() const
{
	return flipVertical;
}

void AnimatedSprite::setLooping(bool loop)
{
	looping = loop;
}

bool AnimatedSprite::getLooping() const
{
	return looping;
}

bool AnimatedSprite::getPlaying() const
{
	return playing;
}

} // end namespace vik
