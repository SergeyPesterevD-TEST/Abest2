#ifndef RF65XDEVICE_INCLUDE
#define RF65XDEVICE_INCLUDE

#if defined(__cplusplus)
extern "C" {
#endif

#include "RFDevice.h"
#include "RFSerialDevice.h"

namespace RFDevice {

	class RFDEVICE_API RF65xDevice : public RFSerialDevice
	{
	public:	
		RF65xDevice(void);
		~RF65xDevice(void);
	
		LPRF65xUDPPACKET pack;		

		void BindNetworkAddress(BYTE ucAddress);
		BOOL HelloCmd();

		BOOL GetSingleMeasure(USHORT* lpusValue);
		BOOL GetStreamMeasure(USHORT* lpusValue);
		BOOL GetSingleDualMeasure8( BYTE* lpbValue  );
		BOOL GetStreamDualMeasure8( BYTE* lpbValue  );
		BOOL StartStream();
		BOOL StopStream();
		BOOL GetDebugArr(void* lpArrayBuf, size_t *lpArraySize);

		BOOL EthernetOpenPort();
		BOOL EthernetGetStreamMeasure();//(LPRF65xUDPPACKET lp65xUDPPacket);

		BOOL EnableSensor(BOOL bEnable = TRUE);
		BOOL SetPriority(BYTE ucValue);
		BOOL SetNetworkAddress(BYTE ucValue);
		BOOL SetBaundRate(DWORD dwValue);
		BOOL SetAverageCount(DWORD dwValue);
		BOOL SetSamplingPeriod(DWORD dwValue);
		BOOL SetNominalValue(DWORD dwValue);
		BOOL SetSynchType(BYTE ucValue);

		BOOL GetPowerState();
		BYTE GetPriority();
		BYTE GetNetworkAddress();
		DWORD GetBaundRate();
		DWORD GetAverageCount();
		DWORD GetSamplingPeriod();
		DWORD GetNominalValue();
		DWORD GetMatrixSize();

		const RF65xPARAMS* GetParams() const;
		
/*		BYTE	GetDeviceType();
		BYTE	GetDeviceModificaton();
		WORD	GetDeviceSerial();
		WORD	GetDeviceMaxDistance();
		WORD	GetDeviceRange();	*/

	protected:
		RF65xPARAMS m_params;	
		RFCOMHELLOANSWER m_helloAnswer;
		
		LPRF60X_HANDLE_CONTEXT m_lphHandle;

		BOOL NetAddressSet();
		void PopulateParams();

		BOOL WriteParameterBOOL(WORD prmCode, BOOL* lpPrmValue, BOOL valueToSet);
		BOOL WriteParameterBYTE(WORD prmCode, BYTE* lpPrmValue, BYTE valueToSet);
		BOOL WriteParameterDWORD(WORD prmCode, DWORD* lpPrmValue, DWORD valueToSet);
	};

}

#if defined(__cplusplus)
}
#endif

#endif //RF65XDEVICE_INCLUDE
