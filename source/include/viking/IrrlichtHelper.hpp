#ifndef VIK_IRRLICHTHELPER_HPP_INCLUDED
#define VIK_IRRLICHTHELPER_HPP_INCLUDED

#include <irrlicht/aabbox3d.h>

namespace irr
{

namespace scene
{

class ISceneNode;

} // end namespace scene

} // end namespace irr

namespace vik
{

irr::core::aabbox3df getSceneNodeCompositeBounds(irr::scene::ISceneNode* root);

int getNodeTreeSize(irr::scene::ISceneNode* node);

} // end namespace vik

#endif // VIK_IRRLICHTHELPER_HPP_INCLUDED
