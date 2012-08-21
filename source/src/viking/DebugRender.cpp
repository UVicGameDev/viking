#include "viking/DebugRender.hpp"

#include <irrlicht/IVideoDriver.h> 
#include "viking/GameApp.hpp"

namespace vik
{

void drawRGBAxis()
{
	irr::video::IVideoDriver* driver = GameApp::getSingleton().getVideoDriver();

	using namespace irr;

	const float axisLength = 100.0f;
	const core::vector3df center(0.0f);
	const core::vector3df arrows[] = {
		center + core::vector3df(axisLength, 0.0f, 0.0f),
		center + core::vector3df(0.0f, axisLength, 0.0f),
		center + core::vector3df(0.0f, 0.0f, axisLength)
	};
	const video::SColor arrow_colors[] = {
		video::SColor(255, 255,   0,   0),
		video::SColor(255,   0, 255,   0),
		video::SColor(255,   0,   0, 255)
	};
	
	video::SMaterial material;
	material.Lighting = false;
	driver->setMaterial(material);
	driver->setTransform(video::ETS_WORLD, core::IdentityMatrix);

	driver->draw3DBox( core::aabbox3df(0.0f,0.0f,0.0f,20.0f,20.0f,20.0f) , video::SColor(255, 255, 255, 255) );
	for (unsigned i = 0; i < sizeof(arrows)/sizeof(*arrows); ++i)
	{
		driver->draw3DLine(center, arrows[i], arrow_colors[i % (sizeof(arrow_colors)/(sizeof(*arrow_colors)))]);
	}
}

} // end namespace vik
