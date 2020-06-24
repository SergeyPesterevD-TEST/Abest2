#ifndef RF651DEVICE_INCLUDE
#define RF651DEVICE_INCLUDE

#if defined(__cplusplus)
extern "C" {
#endif

#include "RFDevice.h"
#include "RF65xDevice.h"

namespace RFDevice {

	class RFDEVICE_API RF651Device : public RF65xDevice
	{
	public:	
		RF651Device();
		~RF651Device();

		BOOL SetBeginAnalogRange(DWORD dwValue);
		BOOL SetEndAnalogRange(DWORD dwValue);
		BOOL SetDualMode();
		BOOL MeasureDual( USHORT *lpusValue1, USHORT *lpusValue2 );
		DWORD GetBeginAnalogRange();
		DWORD GetEndAnalogRange();
	};

}

#if defined(__cplusplus)
}
#endif

#endif //RF651DEVICE_INCLUDE
