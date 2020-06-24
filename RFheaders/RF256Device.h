#ifndef RF256DEVICE_INCLUDE
#define RF256DEVICE_INCLUDE

#if defined(__cplusplus)
extern "C" {
#endif

#include "RFDevice.h"
#include "RF25xDevice.h"

namespace RFDevice {

	class RFDEVICE_API RF256Device : public RF25xDevice
	{
	};
}

#if defined(__cplusplus)
}
#endif

#endif //RF65XDEVICE_INCLUDE
