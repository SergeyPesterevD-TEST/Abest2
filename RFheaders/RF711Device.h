#pragma once

#include "RFDevice.h"
#include "RF65xDevice.h"
#include "RFTypeDefs.h"

#if defined(__cplusplus)
extern "C" {
#endif

namespace RFDevice {

class RFDEVICE_API RF711Device :
	public RF65xDevice
{
public:
	RF711Device(void);
	~RF711Device(void);
	BOOL GetSingleMeasure(PINT32 lpValueX, PINT32 lpValueY);
};

}//namespace

#if defined(__cplusplus)
}
#endif
