#include "viking/ControlScheme.hpp"

namespace vik
{

ControlScheme::ControlScheme(
		irr::EKEY_CODE up,
		irr::EKEY_CODE down,
		irr::EKEY_CODE left,
		irr::EKEY_CODE right):
upKey(up),
downKey(down),
leftKey(left),
rightKey(right)
{
}

bool ControlScheme::isDirectionalKey(irr::EKEY_CODE k) const
{
	return (k == upKey || k == downKey || k == leftKey || k == rightKey);
}


void ControlScheme::serializeAttributes(irr::io::IAttributes* out, irr::io::SAttributeReadWriteOptions* options) const
{
	out->addInt("upKey", upKey);
	out->addInt("downKey", downKey);
	out->addInt("leftKey", leftKey);
	out->addInt("rightKey", rightKey);
}

void ControlScheme::deserializeAttributes(irr::io::IAttributes* in, irr::io::SAttributeReadWriteOptions* options)
{
	upKey = (irr::EKEY_CODE)in->getAttributeAsInt("upKey");
	downKey = (irr::EKEY_CODE)in->getAttributeAsInt("downKey");
	leftKey = (irr::EKEY_CODE)in->getAttributeAsInt("leftKey");
	rightKey = (irr::EKEY_CODE)in->getAttributeAsInt("rightKey");
}

} // end namespace vik
