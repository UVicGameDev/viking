#ifndef VIK_FPSDISPLAY_HPP_INCLUDED
#define VIK_FPSDISPLAY_HPP_INCLUDED

#include "viking/GameObject.hpp"
#include <irrlicht/IGUIStaticText.h>

namespace vik
{

class FPSDisplay : public GameObject
{
public:
	FPSDisplay();
	void update(GameTime& time);
private:
	void updateFPS();
	int currFPS;
	irr::gui::IGUIStaticText* fpsText;
};

} // end namespace vik

#endif // VIK_FPSDISPLAY_HPP_INCLUDED
