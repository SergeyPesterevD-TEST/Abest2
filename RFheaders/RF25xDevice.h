#ifndef RF25XDEVICE_INCLUDE
#define RF25XDEVICE_INCLUDE

#if defined(__cplusplus)
extern "C" {
#endif

#include "RFDevice.h"
#include "RFSerialDevice.h"

namespace RFDevice {

	class RFDEVICE_API RF25xDevice : public RFSerialDevice
	{
	public:	
		RF25xDevice();
		~RF25xDevice();

		BOOL	OpenPort(LPCSTR lpPort_Name, DWORD dwSpeed = BaudDefault);
		void	BindNetworkAddress(BYTE ucAddress);
		BOOL	GetTimeouts(LPDWORD	lpdwReadIntervalTimeout,
			LPDWORD	lpdwReadTotalTimeoutMultiplier,
			LPDWORD	lpdwReadTotalTimeoutConstant,
			LPDWORD	lpdwWriteTotalTimeoutMultiplier, 
			LPDWORD	lpdwWriteTotalTimeoutConstant);
		BOOL	SetTimeouts(DWORD		dwReadIntervalTimeout,
			DWORD		dwReadTotalTimeoutMultiplier,
			DWORD		dwReadTotalTimeoutConstant,
			DWORD		dwWriteTotalTimeoutMultiplier, 
			DWORD		dwWriteTotalTimeoutConstant);
		BOOL	GetSingleMeasure(LPDWORD lpdwValue);
		BOOL	GetStreamMeasure(LPDWORD lpdwValue);
		BOOL	StartStream();
		BOOL	StopStream();

		BOOL	EnableSensor(BOOL bEnable = TRUE);
		BOOL	SetSample(BYTE ucValue);
		BOOL	SetSampleModeToTime();
		BOOL	SetSampleModeToClk();
		BOOL	SetNetworkAddress(BYTE ucValue);
		BOOL	SetBaundRate( DWORD );
		BOOL	SetCoordStartPoint( DWORD );
		BOOL	SetSamplingPeriod( DWORD );
		BOOL	SetBeginAnalogRange( DWORD );
		BOOL	SetEndAnalogRange( DWORD );
		BOOL	SetAnalogOutScaling( DWORD );
		BOOL	SetLowLimitOC( DWORD );
		BOOL	SetUpLimitOC( DWORD );
		BOOL	SetLogicOutPolarity( DWORD );
		BOOL	SetLowLimitOutPolarityHA();
		BOOL	SetLowLimitOutPolarityLA();
		BOOL	SetUpLimitOutPolarityHA();
		BOOL	SetUpLimitOutPolarityLA();

		BOOL	GetPowerState();	
		BYTE	GetSampleMode();
		BOOL	IsSampleModeClk();	
		BYTE	GetNetworkAddress();
		DWORD	GetBaundRate();
		DWORD	GetCoordStartPoint();
		DWORD	GetSamplingPeriod();		
		DWORD	GetBeginAnalogRange();
		DWORD	GetEndAnalogRange();
		DWORD	GetAnalogOutScaling();
		DWORD	GetLowLimitOC();
		DWORD	GetUpLimitOC();
		DWORD	GetLogicOutPolarity();
		BOOL	IsLowLimitOutPolarityHA();
		BOOL	IsUpLimitOutPolarityHA();

		LPRF25XPARAMS GetParams();
		BOOL HelloCmd();

	protected:
		RF25XPARAMS m_params;	
		RFCOMHELLOANSWER m_helloAnswer;

		BOOL NetAddressSet();
		//void PopulateParams();

		BOOL WriteParameterBOOL(WORD prmCode, BOOL* lpPrmValue, BOOL valueToSet);
		BOOL WriteParameterBYTE(WORD prmCode, BYTE* lpPrmValue, BYTE valueToSet);
		BOOL WriteParameterDWORD(WORD prmCode, DWORD* lpPrmValue, DWORD valueToSet);
	};

}

#if defined(__cplusplus)
}
#endif

#endif //RF65XDEVICE_INCLUDE
