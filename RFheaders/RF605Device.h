#ifndef RF605DEVICE_INCLUDE
#define RF605DEVICE_INCLUDE

#if defined(__cplusplus)
extern "C" {
#endif

#include "RFDevice.h"
#include "RF60xDevice.h"

namespace RFDevice {

	class RFDEVICE_API RF605Device : public RF60xDevice
	{
	public:	
		//-----------------------------------------------------------------------------
		//  FUNCTION  RF605Device::RF605Device
		/// \brief    Default constructor of RF605Device object.
		///           
		/// \return   void : N/A
		//-----------------------------------------------------------------------------
		RF605Device(void);

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF605Device::RF605Device
		/// \brief    Default destructor of RF605Device object.
		///           
		/// \return   void : N/A
		//-----------------------------------------------------------------------------
		~RF605Device(void);
	};

}

#if defined(__cplusplus)
}
#endif

#endif //RF605DEVICE_INCLUDE
