#ifndef HASHEDSTRING_HPP_INCLUDED
#define HASHEDSTRING_HPP_INCLUDED

#include <irrlicht/irrTypes.h>

// uncomment the next line to use constexpr hashing algorithm
#define HASHEDSTRING_USE_CONSTEXPR

#ifdef HASHEDSTRING_USE_CONSTEXPR
	#define HASHEDSTRING_CONSTEXPR_IMPL constexpr
#else
	#define HASHEDSTRING_CONSTEXPR_IMPL
#endif

namespace vik
{

// encapsulates hashed strings
// will try to remember the original string in debug builds.
// in release builds, will not store the string at all.
// strings are hashed at compile time whenever possible using constexpr, if the HASHEDSTRING_USE_CONSTEXPR flag is defined.
class HashedString
{
public:
	// Hashes the passed in string and stores the hash
	// in debug builds, the original string pointer will also be stored to be accessed with getDebugString()
	inline explicit HASHEDSTRING_CONSTEXPR_IMPL HashedString(const char* str);

	// in debug builds, will return the originally hashed string.
	// in debug builds, causes undefined behaviour if the string originally used to construct the hash no longer exists. 
	// in release builds, will return an empty string. Should not call this function in release builds.
	inline const char* getReverseHash() const;

	// compares hash by equality
	inline bool operator==(const HashedString& other) const;
	// compares hash in terms of order to allow efficient use with std::less<T> as a Compare function in std::maps
	inline bool operator<(const HashedString& other) const;
	// add more comparison operators as they are needed. Always compare with the hash, not the reverse hash.
private:
	typedef irr::u32 HashType;

	// performs a compile time recursive string hash using the djb2 algorithm explained here: http://www.cse.yorku.ca/~oz/hash.html
	static inline HASHEDSTRING_CONSTEXPR_IMPL HashType hashString(const char* str);
	static inline HASHEDSTRING_CONSTEXPR_IMPL HashType hashStringRecursive(HashType hash, const char* str);

	// reverse hash only exists in debug build
#ifdef _DEBUG
	const char* debugReverseHash;
#endif
	HashType hash;
};

HASHEDSTRING_CONSTEXPR_IMPL HashedString::HashedString(const char* str):
#ifdef _DEBUG
debugReverseHash(str),
#endif
hash(hashString(str))
{
}

HASHEDSTRING_CONSTEXPR_IMPL HashedString::HashType HashedString::hashStringRecursive(HashType hash, const char* str)
{
	return ( !*str ? hash :
		hashStringRecursive(((hash << 5) + hash) + *str, str + 1)); 
}

// performs a compile time string hash
HASHEDSTRING_CONSTEXPR_IMPL HashedString::HashType HashedString::hashString(const char* str)
{
#ifdef HASHEDSTRING_USE_CONSTEXPR
	return ( !str ? 0 :
		hashStringRecursive(5381, str));
#else
	HashType hash = 5381;
	int x;

	while ( (x = *str++) )
	{
		hash += ((hash << 5) + hash) + x;
	}

	return hash;
#endif
}

const char* HashedString::getReverseHash() const
{
#ifdef _DEBUG
	return debugReverseHash;
#else
	return "";
#endif
}

bool HashedString::operator==(const HashedString& other) const
{
	return hash == other.hash;
}

bool HashedString::operator<(const HashedString& other) const
{
	return hash < other.hash;
}

} // end namespace vik

#endif // HASHEDSTRING_HPP_INCLUDED
