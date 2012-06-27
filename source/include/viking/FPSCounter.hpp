#ifndef FPS_COUNTER_HPP_INCLUDED
#define FPS_COUNTER_HPP_INCLUDED

#include "viking/GameObject.hpp"
#include <irrlicht/IGUIStaticText.h>

namespace vik
{

class FPSCounter : public GameObject
{
public:
	FPSCounter();
	void update(GameTime& time);
private:
	void updateFPS();
	int currFPS;
	irr::gui::IGUIStaticText* fpsText;
};

} // end namespace vik

#endif // FPS_COUNTER_HPP_INCLUDED
