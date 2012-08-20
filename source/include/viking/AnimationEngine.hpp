#ifndef VIK_ANIMATIONENGINE_HPP_INCLUDED
#define VIK_ANIMATIONENGINE_HPP_INCLUDED

#include "viking/GameTime.hpp"
#include "viking/AnimatedSpriteData.hpp"
#include "viking/AnimatedSprite.hpp"
#include <string>
#include <memory>

namespace vik
{

class AnimationEngine
{
public:
	// update the state of all animations
	void update(GameTime& time);

	// adds the sprite to the engine and also takes shared ownership of it.
	void addSprite(std::shared_ptr<AnimatedSprite> sprite);

	// releases shared ownership of the given sprite
	void removeSprite(const std::shared_ptr<AnimatedSprite>& sprite);

	// Loads sprite data and returns it. Returns std::shared_ptr() if failed. Sprite data is cached if the flag is set.
	std::shared_ptr<AnimatedSpriteData> load(const std::string& filename, bool cacheIt = true);

	// releases shared ownership of all cached sprite data
	void clearSpriteDataCache();
private:
	std::vector<std::shared_ptr<AnimatedSprite>> spriteList;
	std::vector<std::shared_ptr<AnimatedSpriteData>> spriteDataCache;
};

} // end namespace vik

#endif // VIK_ANIMATIONENGINE_HPP_INCLUDED
