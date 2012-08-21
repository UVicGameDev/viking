#include "viking/ControlScheme.hpp"

namespace vik
{

ControlScheme::ControlScheme(
		irr::EKEY_CODE up,
		irr::EKEY_CODE down,
		irr::EKEY_CODE left,
		irr::EKEY_CODE right,
		irr::EKEY_CODE action0):
upKey(up),
downKey(down),
leftKey(left),
rightKey(right),
actionKey0(action0)
{
}

bool ControlScheme::isDirectionalKey(irr::EKEY_CODE k) const
{
	return (k == upKey || k == downKey || k == leftKey || k == rightKey);
}

bool ControlScheme::isActionKey(irr::EKEY_CODE k) const
{
	return (k == actionKey0);
}

int ControlScheme::getActionKeyIndex(irr::EKEY_CODE k) const
{
	if (k == actionKey0) return 0;
	else return -1;
}

void ControlScheme::serializeAttributes(irr::io::IAttributes* out, irr::io::SAttributeReadWriteOptions* options) const
{
	out->addInt("upKey", upKey);
	out->addInt("downKey", downKey);
	out->addInt("leftKey", leftKey);
	out->addInt("rightKey", rightKey);
	out->addInt("actionKey0", actionKey0);
}

void ControlScheme::deserializeAttributes(irr::io::IAttributes* in, irr::io::SAttributeReadWriteOptions* options)
{
	upKey = (irr::EKEY_CODE)in->getAttributeAsInt("upKey");
	downKey = (irr::EKEY_CODE)in->getAttributeAsInt("downKey");
	leftKey = (irr::EKEY_CODE)in->getAttributeAsInt("leftKey");
	rightKey = (irr::EKEY_CODE)in->getAttributeAsInt("rightKey");
	actionKey0 = (irr::EKEY_CODE)in->getAttributeAsInt("actionKey0");
}

} // end namespace vik
