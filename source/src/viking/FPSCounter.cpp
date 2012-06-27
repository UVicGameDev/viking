#include "viking/FPSCounter.hpp"
#include "viking/GameApp.hpp"
#include <sstream>

using namespace irr;

namespace vik
{

static const wchar_t* FPSString = L"FPS: ";

FPSCounter::FPSCounter():
currFPS(0),
fpsText(0)
{
	gui::IGUIEnvironment* guienv = GameApp::getSingleton().getGUIEnvironment();
	fpsText = guienv->addStaticText(FPSString, core::recti(0,0,50,50));
	fpsText->setOverrideColor(video::SColor(255,255,255,255));

	updateFPS();
}

void FPSCounter::update(GameTime& time)
{
	updateFPS();
}

void FPSCounter::updateFPS()
{
	int lastFPS = currFPS;
	currFPS = GameApp::getSingleton().getVideoDriver()->getFPS();

	if (lastFPS != currFPS)
	{
		std::wstringstream ss;
		ss << FPSString << lastFPS;
		fpsText->setText(ss.str().c_str());

		core::dimension2du screenSize = GameApp::getSingleton().getVideoDriver()->getCurrentRenderTargetSize();
		fpsText->setRelativePosition(core::position2di(screenSize.Width - fpsText->getRelativePosition().getWidth(), 0));
	}
}

} // end namespace vik
