#ifndef VIK_DEBUGRENDER_HPP_INCLUDED
#define VIK_DEBUGRENDER_HPP_INCLUDED

namespace irr
{

namespace video
{

class IVideoDriver;

} // end namespace video

} // end namespace irr

namespace vik
{

// draws red green blue arrows to help know how the X Y Z coordinates work
void drawRGBAxis(irr::video::IVideoDriver* driver);

} // end namespace vik

#endif // VIK_DEBUGRENDER_HPP_INCLUDED
