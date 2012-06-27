#ifndef IRRLICHT_STREAM_HPP
#define IRRLICHT_STREAM_HPP

#include <iostream>
#include <irrlicht/vector2d.h>
#include <irrlicht/vector3d.h>
#include <irrlicht/aabbox3d.h>

namespace vik
{

template<class T>
std::ostream& operator<<(std::ostream& os, irr::core::vector2d<T>& v)
{
	os << "{ " << v.X << ", " << v.Y << " }";
	return os;
}

template<class T>
std::ostream& operator<<(std::ostream& os, irr::core::vector3d<T>& v)
{
	os << "{ " << v.X << ", " << v.Y << ", " << v.Z << " }";
	return os;
}

template<class T>
std::ostream& operator<<(std::ostream& os, irr::core::aabbox3d<T> b)
{
	os << "{ Min " << b.MinEdge << ", Max " << b.MaxEdge << " }";
	return os;
}

} // end namespace vik

#endif // IRRLICHT_STREAM_HPP
