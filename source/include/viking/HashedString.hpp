#ifndef VIK_HASHSTRING_HPP_INCLUDED
#define VIK_HASHSTRING_HPP_INCLUDED

#include <irrlicht/irrTypes.h>

namespace vik
{

typedef irr::u32 HashedString;

// performs a compile time recursive string hash using the djb2 algorithm explained here: http://www.cse.yorku.ca/~oz/hash.html
// do not use this function, call hashString instead.
constexpr HashedString _hashStringRecursive(HashedString hash, const char* str)
{
	return ( !*str ? hash :
	_hashStringRecursive(((hash << 5) + hash) + *str, str + 1)); 
}

// performs a compile time string hash
constexpr HashedString hashString(const char* str)
{
	return ( !str ? 0 :
	_hashStringRecursive(5381, str));
}

} // end namespace vik

#endif // VIK_HASHSTRING_HPP_INCLUDED
