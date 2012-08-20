#ifndef VIK_IRRLICHT_STREAM_HPP
#define VIK_IRRLICHT_STREAM_HPP

#include <iostream>
#include <irrlicht/vector2d.h>
#include <irrlicht/vector3d.h>
#include <irrlicht/aabbox3d.h>
#include <irrlicht/SColor.h>
#include <irrlicht/S3DVertex.h>

namespace vik
{

template<class T>
std::ostream& operator<<(std::ostream& os, const irr::core::vector2d<T>& v)
{
	os << "{ " << v.X << ", " << v.Y << " }";
	return os;
}

template<class T>
std::ostream& operator<<(std::ostream& os, const irr::core::vector3d<T>& v)
{
	os << "{ " << v.X << ", " << v.Y << ", " << v.Z << " }";
	return os;
}

template<class T>
std::ostream& operator<<(std::ostream& os, const irr::core::aabbox3d<T>& b)
{
	os << "{ Min " << b.MinEdge << ", Max " << b.MaxEdge << " }";
	return os;
}

template<class T>
std::ostream& operator<<(std::ostream& os, const irr::core::string<T>& s)
{
	os << s.c_str();
	return os;
}

inline std::ostream& operator<<(std::ostream& os, const irr::video::SColor& c)
{
	os << "{ RGBA:"
	<< ' ' << c.getRed()
	<< ' ' << c.getGreen()
	<< ' ' << c.getBlue()
	<< ' ' << c.getAlpha()
	<< " }";

	return os;
}

inline std::ostream& operator<<(std::ostream& os, const irr::video::S3DVertex& v)
{
	os << "{"
	<< " Color: " << v.Color
	<< " Normal: " << v.Normal
	<< " Pos: " << v.Pos
	<< " TCoords: " << v.TCoords
	<< " }";

	return os;
}

} // end namespace vik

#endif // IRRLICHT_STREAM_HPP
