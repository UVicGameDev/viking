#ifndef VIK_PARTICLEANIMATOR_HPP_INCLUDED
#define VIK_PARTICLEANIMATOR_HPP_INCLUDED

#include <memory>
#include "viking/GameTime.hpp"

namespace vik
{

// Moves particles without claiming ownership of them.
class ParticleAnimator
{
public:
	ParticleAnimator(std::weak_ptr<Particle>& animated):
	animated(animated)
	{
	}

	virtual ~ParticleAnimator(){}

	// updates animation
	// must manually track if it should animated based on playing or not based on your implementation.
	virtual void update(GameTime& time) = 0;
private:
	std::weak_ptr<Particle> animated;
};

} // end namespace vik

#endif // VIK_PARTICLE_ANIMATOR_HPP_INCLUDED
