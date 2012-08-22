#ifndef VIK_CONTROLSCHEME_HPP_INCLUDED
#define VIK_CONTROLSCHEME_HPP_INCLUDED

#include "viking/Serializable.hpp"
#include <irrlicht/Keycodes.h>

namespace vik
{

// The control scheme to define for a single player
// TODO: abstract key IDs beyond the integers of EKEY_CODEs just for serialization
class ControlScheme : public Serializable
{
public:
	ControlScheme() = default;

	ControlScheme(
		irr::EKEY_CODE up,
		irr::EKEY_CODE down,
		irr::EKEY_CODE left,
		irr::EKEY_CODE right,
		irr::EKEY_CODE action0);

	bool isDirectionalKey(irr::EKEY_CODE k) const;

	bool isActionKey(irr::EKEY_CODE k) const;

	// returns -1 if it isn't an action key
	int getActionKeyIndex(irr::EKEY_CODE k) const;

	void serializeAttributes(irr::io::IAttributes* out, irr::io::SAttributeReadWriteOptions* options=0) const override;
	void deserializeAttributes(irr::io::IAttributes* in, irr::io::SAttributeReadWriteOptions* options=0) override;

	irr::EKEY_CODE upKey;
	irr::EKEY_CODE downKey;
	irr::EKEY_CODE leftKey;
	irr::EKEY_CODE rightKey;
	irr::EKEY_CODE actionKey0;
};

} // end namespace vik

#endif // VIK_CONTROLSCHEME_HPP_INCLUDED
