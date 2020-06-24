#ifndef RF656DEVICE_INCLUDE
#define RF656DEVICE_INCLUDE

#if defined(__cplusplus)
extern "C" {
#endif

#include "RFDevice.h"
#include "RF65xDevice.h"

namespace RFDevice {

	class RFDEVICE_API RF656Device : public RF65xDevice
	{
	public:	
		RF656Device();
		~RF656Device();

		BOOL SetResTypeBoundaryQuantity( DWORD );
		BOOL SetControlBoundaryNumber( DWORD );
		BOOL SetLowLimit( DWORD );
		BOOL SetUpLimit( DWORD );
		BOOL SetOutputLogicControl( DWORD );
		DWORD GetResTypeBoundaryQuantity();
		DWORD GetControlBoundaryNumber();
		DWORD GetLowLimit();
		DWORD GetUpLimit();
		DWORD GetOutputLogicControl();
		BOOL MeasureDual(USHORT *lpusValue1, USHORT *lpusValue2);
	};

}

#if defined(__cplusplus)
}
#endif

#endif //RF656DEVICE_INCLUDE
