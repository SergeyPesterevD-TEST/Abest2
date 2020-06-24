#ifndef RFLANDEVICE_INCLUDE
#define RFLANDEVICE_INCLUDE

#if defined(__cplusplus)
extern "C" {
#endif

#include "RFDevice.h"

namespace RFDevice {

	class RFDEVICE_API RFEthernetDevice : public RFDeviceObject
	{
	public:
		//-----------------------------------------------------------------------------
		//  FUNCTION  RFEthernetDevice::RFEthernetDevice
		/// \brief    This is constructor of generic RFEthernetDevice object
		///           
		/// \return   none
		//-----------------------------------------------------------------------------
		RFEthernetDevice();
		//-----------------------------------------------------------------------------
		//  FUNCTION  RFEthernetDevice::~RFEthernetDevice
		/// \brief    This is destructor of generic RFEthernetDevice object
		///           
		/// \return   none
		//-----------------------------------------------------------------------------
		~RFEthernetDevice();

		SOCKET GetSocket();

	protected:
		SOCKET m_sock;
	};

}

#if defined(__cplusplus)
}
#endif

#endif //RFLANDEVICE_INCLUDE
