#include "viking/IrrlichtHelper.hpp"
#include "viking/GameApp.hpp"

#include <irrlicht/irrlicht.h>

using namespace irr;

namespace vik
{

core::aabbox3df getSceneNodeCompositeBounds(scene::ISceneNode* root)
{
	core::aabbox3df boundaries;
	if (root != GameApp::getSingleton().getSceneManager()->getRootSceneNode())
	{
		boundaries.addInternalBox(root->getTransformedBoundingBox());
	}
	for (auto it = root->getChildren().begin(); it != root->getChildren().end(); ++it)
	{
		if ((*it)->isVisible())
		{
			boundaries.addInternalBox(getSceneNodeCompositeBounds(*it));
		}
	}
	return boundaries;
}

int getNodeTreeSize(irr::scene::ISceneNode* node)
{
	int numChildren = 1;
	for (auto it = node->getChildren().begin(); it != node->getChildren().end(); ++it)
	{
		numChildren += getNodeTreeSize(*it);
	}
	return numChildren;
}

} // end namespace vik
