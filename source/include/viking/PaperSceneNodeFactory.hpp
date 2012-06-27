#ifndef PAPER_SCENE_NODE_FACTORY_HPP_INCLUDED
#define PAPER_SCENE_NODE_FACTORY_HPP_INCLUDED

#include <irrlicht/ITexture.h>
#include <irrlicht/ISceneNode.h>
#include <irrlicht/ISceneManager.h>

namespace vik
{

class PaperSceneNodeFactory
{
public:
	PaperSceneNodeFactory(irr::scene::ISceneManager* smgr);
	irr::scene::ISceneNode* create(irr::video::ITexture* tex);
private:
	irr::scene::ISceneManager* smgr;
};

} // end namespace vik

#endif // PAPER_SCENE_NODE_FACTORY_HPP_INCLUDED
