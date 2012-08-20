#ifndef VIK_SERIALIZABLE_HPP_INCLUDED
#define VIK_SERIALIZABLE_HPP_INCLUDED

#include <irrlicht/IAttributeExchangingObject.h>
#include <irrlicht/IAttributes.h>

namespace vik
{

// interface for serializable classes
// follows the exact same interface as Irrlicht's serializable class.
// Its documentation is here: http://irrlicht.sourceforge.net/docu/classirr_1_1io_1_1_i_attribute_exchanging_object.html
// For an example, see lines 713 and 736 of http://irrlicht.sourceforge.net/docu/_i_g_u_i_element_8h_source.html
class Serializable
{
public:
	virtual void serializeAttributes(irr::io::IAttributes* out, irr::io::SAttributeReadWriteOptions* options=0) const = 0;
	virtual void deserializeAttributes(irr::io::IAttributes* in, irr::io::SAttributeReadWriteOptions* options=0) = 0;
};

} // end namespace vik

#endif // VIK_SERIALIZABLE_HPP_INCLUDED
