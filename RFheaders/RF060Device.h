#ifndef RF060DEVICE_INCLUDE
#define RF060DEVICE_INCLUDE

#if defined(__cplusplus)
extern "C" {
#endif

#include "RFDevice.h"
#include "RF605Device.h"

namespace RFDevice {

	class RFDEVICE_API RF060Device : public RF605Device
	{
	public:	
		RF060Device(void);
		~RF060Device(void);

		BOOL	HelloCmd(BYTE bAddress, LPRFCOMHELLOANSWER lprfHelloAnswer);
		BOOL	OpenPort(LPCSTR lpPort_Name, DWORD dwSpeed);
		BOOL	GetMeasure(BYTE bAddress, USHORT* lpusValue, USHORT* lpSW);
	};

}

#if defined(__cplusplus)
}
#endif

#endif //RF060DEVICE_INCLUDE
