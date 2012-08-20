#ifndef VIK_HASHSTRING_HPP_INCLUDED
#define VIK_HASHSTRING_HPP_INCLUDED

#include <irrlicht/irrTypes.h>
#include <iostream>

namespace vik
{

typedef irr::u32 HashTypeDetail;

// performs a compile time recursive string hash using the djb2 algorithm explained here: http://www.cse.yorku.ca/~oz/hash.html
constexpr HashTypeDetail hashStringRecursiveDetail(HashTypeDetail h, const char* str)
{
	return ( !*str ? h :
	hashStringRecursiveDetail(((h << 5) + h) + *str, str + 1)); 
}

// performs a compile time string hash
constexpr HashTypeDetail hashStringDetail(const char* str)
{
	return ( !str ? 0 :
	hashStringRecursiveDetail(5381, str));
}

class HashedString;

inline std::ostream& operator<<(std::ostream& os, const HashedString& h);

class HashedString
{
public:
	friend std::ostream& operator<<(std::ostream& os, const HashedString& h);

	explicit constexpr HashedString(const char *str):
	hash(hashStringDetail(str))
#ifdef DEBUG
	,reverseHash(str)
#endif
	{
	}

	constexpr irr::u32 toU32() const
	{
		return hash;
	}

	const char* getReverseHash() const
	{
#ifdef DEBUG
		return reverseHash;
#else
		return 0;
#endif
	}

	constexpr bool operator==(const HashedString& other)
	{
		return hash == other.hash;
	}

	constexpr bool operator!=(const HashedString& other)
	{
		return hash != other.hash;
	}

	constexpr bool operator<(const HashedString& other)
	{
		return hash < other.hash;
	}

	constexpr bool operator>(const HashedString& other)
	{
		return hash > other.hash;
	}

	constexpr bool operator<=(const HashedString& other)
	{
		return hash <= other.hash;
	}

	constexpr bool operator>=(const HashedString& other)
	{
		return hash >= other.hash;
	}

private:
	HashTypeDetail hash;
#ifdef DEBUG
	const char *reverseHash;
#endif
};

std::ostream& operator<<(std::ostream& os, const HashedString& h)
{
	os << h.hash;
	return os;
}

} // end namespace vik

#endif // VIK_HASHSTRING_HPP_INCLUDED
