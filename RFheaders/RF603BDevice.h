#ifndef RF603BDEVICE_INCLUDE
#define RF603BDEVICE_INCLUDE

#if defined(__cplusplus)
extern "C" {
#endif

#include "RFDevice.h"
#include "RF605Device.h"
#include "RFTypeDefs.h"

namespace RFDevice {

	class RFDEVICE_API RF603BDevice : public RF605Device
	{
	public:
		RF603BDevice();
		~RF603BDevice();

		BOOL EthernetGetStreamMeasure( LPRF60xBUDPPACKET );	
		// lpValues => float[100]
		BOOL EthernetGetNormalisedStreamMeasure(float* OUT lpValues);

		static WORD Compare(RF60xBUDPVALUE value1, RF60xBUDPVALUE value2);
	};

}

#if defined(__cplusplus)
}
#endif

#endif //RF603DEVICE_INCLUDE
