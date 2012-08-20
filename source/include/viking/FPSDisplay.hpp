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

	void serializeAttributes(irr::io::IAttributes* out, irr::io::SAttributeReadWriteOptions* options=0) const override;
	void deserializeAttributes(irr::io::IAttributes* in, irr::io::SAttributeReadWriteOptions* options=0) override;
private:
	void updateFPS();
	int currFPS;
	irr::gui::IGUIStaticText* fpsText;
};

} // end namespace vik

#endif // VIK_FPSDISPLAY_HPP_INCLUDED
