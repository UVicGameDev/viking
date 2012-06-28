#ifndef FPS_DISPLAY_HPP_INCLUDED
#define FPS_DISPLAY_HPP_INCLUDED

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

#endif // FPS_DISPLAY_HPP_INCLUDED
